#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

const int CV_GUI_NORMAL= 0x10;

int main( int argc, const char** argv )
{
	// Read images
	Mat lena= imread("../lena.jpg");
	
	// Create windows
	namedWindow("Lena");
	
	// show images
	imshow("Lena", lena);
	
	// Display Overlay
	displayOverlay("Lena", "Overlay 5secs", 5000);

	// Display Status Bar
	displayStatusBar("Lena", "Status bar 5secs", 5000);

	// Save window parameters
	saveWindowParameters("Lena");

	// load Window parameters
	loadWindowParameters("Lena");

	// wait for any key press
	waitKey(0);

	// Destroy the windows
	destroyWindow("Lena");
	
	return 0;
}