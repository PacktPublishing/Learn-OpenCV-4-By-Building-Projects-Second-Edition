// OPTICAL FLOW USING FARNEBACK ALGORITHM

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

// Function to compute the optical flow map
void drawOpticalFlow(const Mat& flowImage, Mat& flowImageGray)
{
    int stepSize = 16;
    Scalar color = Scalar(0, 255, 0);
    
    // Draw the uniform grid of points on the input image along with the motion vectors
    for(int y = 0; y < flowImageGray.rows; y += stepSize)
    {
        for(int x = 0; x < flowImageGray.cols; x += stepSize)
        {
            // Circles to indicate the uniform grid of points
            int radius = 2;
            int thickness = -1;
            circle(flowImageGray, Point(x,y), radius, color, thickness);
            
            // Lines to indicate the motion vectors
            Point2f pt = flowImage.at<Point2f>(y, x);
            line(flowImageGray, Point(x,y), Point(cvRound(x+pt.x), cvRound(y+pt.y)), color);
        }
    }
}

int main(int, char** argv)
{
    // Create the capture object
    // 0 -> input arg that specifies it should take the input from the webcam
    VideoCapture cap(0);
    
    if(!cap.isOpened())
    {
        cerr << "Unable to open the webcam. Exiting!" << endl;
        return -1;
    }
    
    char ch;
    Mat curGray, prevGray, flowImage, flowImageGray, frame;
    string windowName = "Optical Flow";
    namedWindow(windowName, 1);
    float scalingFactor = 0.75;
    
    // Iterate until the user presses the Esc key
    while(true)
    {
        // Capture the current frame
        cap >> frame;
        
        if(frame.empty())
            break;
        
        // Resize the frame
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);
        
        // Convert to grayscale
        cvtColor(frame, curGray, COLOR_BGR2GRAY);
        
        // Check if the image is valid
        if(prevGray.data)
        {
            // Initialize parameters for the optical flow algorithm
            float pyrScale = 0.5;
            int numLevels = 3;
            int windowSize = 15;
            int numIterations = 3;
            int neighborhoodSize = 5;
            float stdDeviation = 1.2;
            
            // Calculate optical flow map using Farneback algorithm
            calcOpticalFlowFarneback(prevGray, curGray, flowImage, pyrScale, numLevels, windowSize, numIterations, neighborhoodSize, stdDeviation, OPTFLOW_USE_INITIAL_FLOW);
            
            // Convert to 3-channel RGB
            cvtColor(prevGray, flowImageGray, COLOR_GRAY2BGR);
            
            // Draw the optical flow map
            drawOpticalFlow(flowImage, flowImageGray);
            
            // Display the output image
            imshow(windowName, flowImageGray);
        }
        
        // Break out of the loop if the user presses the Esc key
        ch = waitKey(10);
        if(ch == 27)
            break;
        
        // Swap previous image with the current image
        std::swap(prevGray, curGray);
    }
    
    return 0;
}


