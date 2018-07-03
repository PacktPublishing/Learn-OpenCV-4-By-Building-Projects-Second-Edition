#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main( int argc, const char** argv )
{
	// Read images
	Mat color= imread("../lena.jpg");
	Mat gray= imread("../lena.jpg", IMREAD_GRAYSCALE);
	
	// Write images
	imwrite("lenaGray.jpg", gray);
	
	// Get same pixel with opencv function
	int myRow=color.cols-1;
	int myCol=color.rows-1;
	auto pixel= color.at<Vec3b>(myRow, myCol);
	cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;
	
	// show images
	imshow("Lena BGR", color);
	imshow("Lena Gray", gray);
	// wait for any key press
	waitKey(0);
	return 0;
}
