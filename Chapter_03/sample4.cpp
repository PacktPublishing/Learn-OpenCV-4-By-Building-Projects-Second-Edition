#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

Mat img;
bool applyGray=false;
bool applyBlur=false;
bool applySobel=false;

void applyFilters(){
	Mat result;
	img.copyTo(result);
	if(applyGray){
		cvtColor(result, result, COLOR_BGR2GRAY);
	}
	if(applyBlur){
		blur(result, result, Size(5,5));	
	}
	if(applySobel){
		Sobel(result, result, CV_8U, 1, 1);	
	}
	imshow("Lena", result);
}

void grayCallback(int state, void* userData)
{
	applyGray= true;
	applyFilters();
}
void bgrCallback(int state, void* userData)
{
	applyGray= false;
	applyFilters();
}

void blurCallback(int state, void* userData)
{
	applyBlur= (bool)state;
	applyFilters();
}

void sobelCallback(int state, void* userData)
{
	applySobel= !applySobel;
	applyFilters();
}

int main( int argc, const char** argv )
{
	// Read images
	img= imread("../lena.jpg");
	
	// Create windows
	namedWindow("Lena");
	
	// create Buttons
	createButton("Blur", blurCallback, NULL, QT_CHECKBOX, 0);

	createButton("Gray",grayCallback,NULL,QT_RADIOBOX, 0);
	createButton("RGB",bgrCallback,NULL,QT_RADIOBOX, 1);

	createButton("Sobel",sobelCallback,NULL,QT_PUSH_BUTTON, 0);
	
	// wait app for a key to exit
	waitKey(0);
	
	// Destroy the windows
	destroyWindow("Lena");
	
	return 0;
}