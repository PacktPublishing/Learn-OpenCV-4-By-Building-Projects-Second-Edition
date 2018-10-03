#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

#include <vector>
#include <fstream>

using namespace std;
using namespace cv;

Mat binarize(Mat input) 
{	
	//Uses otsu to threshold the input image
	Mat binaryImage;
	cvtColor(input, input, COLOR_BGR2GRAY);
	threshold(input, binaryImage, 0, 255, THRESH_OTSU);

	//Count the number of black and white pixels
	int white = countNonZero(binaryImage);
	int black = binaryImage.size().area() - white;

	//If the image is mostly white (white background), invert it
	return white < black ? binaryImage : ~binaryImage;
}

vector<RotatedRect> findTextAreas(Mat input) {
	//Dilate the image
	auto kernel = getStructuringElement(MORPH_CROSS, Size(3,3));
	Mat dilated;
	dilate(input, dilated, kernel, cv::Point(-1, -1), 5);
	imshow("Dilated", dilated);
	waitKey(0);

	//Find all image contours
	vector<vector<Point> > contours;
	findContours(dilated, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//For each contour
	vector<RotatedRect> areas;
	for (const auto& contour : contours)
	{	
		//Find it's rotated rect
		auto box = minAreaRect(contour);

		//Discard very small boxes
		if (box.size.width < 20 || box.size.height < 20)
			continue;

		//Discard squares shaped boxes and boxes 
		//higher than larger
		double proportion = box.angle < -45.0 ?
			box.size.height / box.size.width : 
			box.size.width / box.size.height;

		if (proportion < 2) 
			continue;

		//Add the box
		areas.push_back(box);
	}
	return areas;
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

tesseract::TessBaseAPI ocr;

const char* identifyText(Mat input, const char* language = "eng")
{	
	ocr.Init(NULL, language, tesseract::OEM_TESSERACT_ONLY);	
	ocr.SetVariable("tessedit_write_images", "1");
	ocr.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
	ocr.SetImage(input.data, input.cols, input.rows, input.elemSize(), input.cols);
	
	const char* text = ocr.GetUTF8Text();
	cout << "Text:" << endl;
	cout << text << endl;
	cout << "Confidence: " << ocr.MeanTextConf() << endl << endl;
	
    // Get the text    
	return text;
}


int main(int argc, char* argv[]) 
{
	//Loads the ticket image and binarize it
	Mat ticket = binarize(imread("ticketHigh.png"));	
	auto regions = findTextAreas(ticket);

	std::ofstream file; 
	file.open("ticket.txt", std::ios::out | std::ios::binary);

	//For each region
	for (const auto& region : regions) {
		//Crop 
		auto cropped = deskewAndCrop(ticket, region);
		auto text = identifyText(cropped, "por");
		
		file.write(text, strlen(text));
		file << endl;
	}
	
	file.close();
}
