#include  "opencv2/highgui.hpp"
#include  "opencv2/imgproc.hpp"
#include  "opencv2/text.hpp"

#include  <vector>
#include  <iostream>

using namespace std;
using namespace cv;
using namespace cv::text;

vector<Mat> separateChannels(const Mat& src)
{
	vector<Mat> channels;
	//Grayscale images
	if (src.type() == CV_8U || src.type() == CV_8UC1) {
		channels.push_back(src);
		channels.push_back(255-src);
		return channels;
	}

	//Colored images
	if (src.type() == CV_8UC3) {
		computeNMChannels(src, channels);
		int size = static_cast<int>(channels.size())-1;
		for (int c = 0; c < size; c++)
			channels.push_back(255-channels[c]);
		return channels;
	}

	//Other types
	cout << "Invalid image format!" << endl;
	exit(-1);	
}

cv::Ptr<BaseOCR> initOCR(const string& ocr) 
{
	if (ocr == "hmm") {
		Mat transitions;
		FileStorage fs("OCRHMM_transitions_table.xml", FileStorage::READ);
		fs["transition_probabilities"] >> transitions;
		fs.release();

		return OCRHMMDecoder::create(
			loadOCRHMMClassifierNM("OCRHMM_knn_model_data.xml.gz"),				//Trained models
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",   //Vocabulary
			transitions,														//Trained transition probabilities
			Mat::eye(62,62,CV_64FC1));											//Emission probabilities. Identity matrix.
	} else if (ocr == "tesseract" || ocr == "tess") {		
		return OCRTesseract::create(nullptr, "eng+por");		
	}

	throw string("Invalid OCR engine: ") + ocr;	
}

Mat deskewAndCrop(Mat input, const RotatedRect& box)
{
	double angle = box.angle;	
	auto size = box.size;

	//Adjust the box angle
   if (angle < -45.0) 
	{
        angle += 90.0;
        std::swap(size.width, size.height);		
	}
	
	//Rotate the text according to the angle
	auto transform = getRotationMatrix2D(box.center, angle, 1.0);
	Mat rotated;
	warpAffine(input, rotated, transform, input.size(), INTER_CUBIC);

	//Crop the result
	Mat cropped;
	getRectSubPix(rotated, size, box.center, cropped);
	copyMakeBorder(cropped,cropped,10,10,10,10,BORDER_CONSTANT,Scalar(0));
	return cropped;
}

Mat drawER(const vector<Mat> &channels, const vector<vector<ERStat> > &regions, const vector<Vec2i>& group, const Rect& rect)
{
	Mat out = Mat::zeros(channels[0].rows+2, channels[0].cols+2, CV_8UC1);

	int flags = 4					//4 neighbors
		+ (255 << 8)				//paint mask in white (255)
		+ FLOODFILL_FIXED_RANGE		//fixed range
		+ FLOODFILL_MASK_ONLY;		//Paint just the mask
	
    for (int g=0; g < group.size(); g++)
    {
		int idx = group[g][0];		
        auto er = regions[idx][group[g][1]];

		//Ignore root region
        if (er.parent == NULL) 
			continue;

		//Transform the linear pixel value to row and col
		int px = er.pixel % channels[idx].cols;
		int py = er.pixel / channels[idx].cols;
		
		//Create the point and adds it to the list.
		Point p(px, py);		

		//Draw the extremal region
        floodFill(
			channels[idx], out,				//Image and mask
			p, Scalar(255),					//Seed and color
			nullptr,						//No rect
			Scalar(er.level),Scalar(0),		//LoDiff and upDiff
			flags							//Flags
		);		
    }
	
	//Crop just the text area and find it's points
	out = out(rect);

	vector<Point> points;	
	findNonZero(out, points);
	//Use deskew and crop to crop it perfectly
	return deskewAndCrop(out, minAreaRect(points));
}

int main(int argc, const char * argv[])
{
	const char* image = argc < 2 ? "easel.png" : argv[1];
    auto input = imread(image);	

	//Convert the input image to grayscale.
	//Just do Mat processed = input; to work with colors.
	Mat processed;
	cvtColor(input, processed, COLOR_RGB2GRAY);

	auto channels = separateChannels(processed);

    // Create ERFilter objects with the 1st and 2nd stage classifiers
    auto filter1 = createERFilterNM1(loadClassifierNM1("trained_classifierNM1.xml"),15,0.00015f,0.13f,0.2f,true,0.1f);
    auto filter2 = createERFilterNM2(loadClassifierNM2("trained_classifierNM2.xml"),0.5);

	//Extract text regions using Newmann & Matas algorithm
	cout << "Processing " << channels.size() << " channels..." << endl;
    vector<vector<ERStat> > regions(channels.size());
    for (int c=0; c < channels.size(); c++)
    {
		cout << "    Channel " << (c+1) << endl;
        filter1->run(channels[c], regions[c]);
        filter2->run(channels[c], regions[c]);		
    }    
    filter1.release();
    filter2.release();

    //Separate character groups from regions
    vector< vector<Vec2i> > groups;
    vector<Rect> groupRects;
    erGrouping(input, channels, regions, groups, groupRects, ERGROUPING_ORIENTATION_HORIZ);
    //erGrouping(input, channels, regions, groups, groupRects, ERGROUPING_ORIENTATION_ANY, "trained_classifier_erGrouping.xml", 0.5);

    // text detection	
	cout << endl << "Detected text:" << endl;
	cout << "-------------" << endl;
	auto ocr = initOCR("tesseract");
	for (int i = 0; i < groups.size(); i++) 
	{
		 auto wordImage = drawER(channels, regions, groups[i], groupRects[i]);

		 string word;
		 ocr->run(wordImage, word);
		 cout << word << endl;
	}
}

