// GOOD FEATURES TO TRACK

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    // Read the input value for the number of corners
    int numCorners;
    istringstream iss(argv[1]);
    iss >> numCorners;
    
    // Check if 'numCorners' is positive
    if( numCorners < 1 )
    {
        numCorners = 1;
    }

    RNG rng(12345);
    string windowName = "Feature points";
    
    // Current frame
    Mat frame, frameGray;
    
    char ch;
    
    // Create the capture object
    // 0 -> input arg that specifies it should take the input from the webcam
    VideoCapture cap(0);
    
    if(!cap.isOpened())
    {
        cerr << "Unable to open the webcam. Exiting!" << endl;
        return -1;
    }
    
    // Scaling factor to resize the input frames from the webcam
    float scalingFactor = 0.75;
    
    // Iterate until the user presses the Esc key
    while(true)
    {
        // Capture the current frame
        cap >> frame;
        
        // Resize the frame
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);
        
        // Convert to grayscale
        cvtColor(frame, frameGray, COLOR_BGR2GRAY );
        
        // Initialize the parameters for Shi-Tomasi algorithm
        vector<Point2f> corners;
        double qualityThreshold = 0.02;
        double minDist = 15;
        int blockSize = 5;
        bool useHarrisDetector = false;
        double k = 0.07;
        
        // Clone the input frame
        Mat frameCopy;
        frameCopy = frame.clone();
        
        // Apply corner detection
        goodFeaturesToTrack(frameGray, corners, numCorners, qualityThreshold, minDist, Mat(), blockSize, useHarrisDetector, k);
        
        // Parameters for the circles to display the corners
        int radius = 8;      // radius of the cirles
        int thickness = 2;   // thickness of the circles
        int lineType = 8;
        
        // Draw the detected corners using circles
        for(size_t i = 0; i < corners.size(); i++)
        {
            Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
            circle(frameCopy, corners[i], radius, color, thickness, lineType, 0);
        }
        
        /// Show what you got
        imshow(windowName, frameCopy);
        
        // Get the keyboard input and check if it's 'Esc'
        // 27 -> ASCII value of 'Esc' key
        ch = waitKey(30);
        if (ch == 27) {
            break;
        }
    }
    
    // Release the video capture object
    cap.release();
    
    // Close all windows
    destroyAllWindows();
    
    return 1;
}

