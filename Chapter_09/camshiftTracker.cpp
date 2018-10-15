// CAMSHIFT TRACKER

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

Mat image;
Point originPoint;
Rect selectedRect;
bool selectRegion = false;
int trackingFlag = 0;

// Function to track the mouse events
void onMouse(int event, int x, int y, int, void*)
{
    if(selectRegion)
    {
        selectedRect.x = MIN(x, originPoint.x);
        selectedRect.y = MIN(y, originPoint.y);
        selectedRect.width = std::abs(x - originPoint.x);
        selectedRect.height = std::abs(y - originPoint.y);
        
        selectedRect &= Rect(0, 0, image.cols, image.rows);
    }
    
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
            originPoint = Point(x,y);
            selectedRect = Rect(x,y,0,0);
            selectRegion = true;
            break;
            
        case EVENT_LBUTTONUP:
            selectRegion = false;
            if( selectedRect.width > 0 && selectedRect.height > 0 )
            {
                trackingFlag = -1;
            }
            break;
    }
}

int main(int argc, char* argv[])
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
    Rect trackingRect;
    
    // range of values for the 'H' channel in HSV ('H' stands for Hue)
    float hueRanges[] = {0,180};
    const float* histRanges = hueRanges;
    
    // min value for the 'S' channel in HSV ('S' stands for Saturation)
    int minSaturation = 40;
    
    // min and max values for the 'V' channel in HSV ('V' stands for Value)
    int minValue = 20, maxValue = 245;
    
    // size of the histogram bin
    int histSize = 8;
    
    string windowName = "CAMShift Tracker";
    namedWindow(windowName, 0);
    setMouseCallback(windowName, onMouse, 0);
    
    Mat frame, hsvImage, hueImage, mask, hist, backproj;
    
    // Image size scaling factor for the input frames from the webcam
    float scalingFactor = 0.75;
    
    // Iterate until the user presses the Esc key
    while(true)
    {
        // Capture the current frame
        cap >> frame;
    
        // Check if 'frame' is empty
        if(frame.empty())
            break;
        
        // Resize the frame
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);
    
        // Clone the input frame
        frame.copyTo(image);
    
        // Convert to HSV colorspace
        cvtColor(image, hsvImage, COLOR_BGR2HSV);
        
        if(trackingFlag)
        {
            // Check for all the values in 'hsvimage' that are within the specified range
            // and put the result in 'mask'
            inRange(hsvImage, Scalar(0, minSaturation, minValue), Scalar(180, 256, maxValue), mask);
            
            // Mix the specified channels
            int channels[] = {0, 0};
            hueImage.create(hsvImage.size(), hsvImage.depth());
            mixChannels(&hsvImage, 1, &hueImage, 1, channels, 1);
            
            if(trackingFlag < 0)
            {
                // Create images based on selected regions of interest
                Mat roi(hueImage, selectedRect), maskroi(mask, selectedRect);
                
                // Compute the histogram and normalize it
                calcHist(&roi, 1, 0, maskroi, hist, 1, &histSize, &histRanges);
                normalize(hist, hist, 0, 255, NORM_MINMAX);
                
                trackingRect = selectedRect;
                trackingFlag = 1;
            }
            
            // Compute the histogram back projection
            calcBackProject(&hueImage, 1, 0, hist, backproj, &histRanges);
            backproj &= mask;
            RotatedRect rotatedTrackingRect = CamShift(backproj, trackingRect, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
            
            // Check if the area of trackingRect is too small
            if(trackingRect.area() <= 1)
            {
                // Use an offset value to make sure the trackingRect has a minimum size
                int cols = backproj.cols, rows = backproj.rows;
                int offset = MIN(rows, cols) + 1;
                trackingRect = Rect(trackingRect.x - offset, trackingRect.y - offset, trackingRect.x + offset, trackingRect.y + offset) & Rect(0, 0, cols, rows);
            }
            
            // Draw the ellipse on top of the image
            ellipse(image, rotatedTrackingRect, Scalar(0,255,0), 3, LINE_AA);
        }
        
        // Apply the 'negative' effect on the selected region of interest
        if(selectRegion && selectedRect.width > 0 && selectedRect.height > 0)
        {
            Mat roi(image, selectedRect);
            bitwise_not(roi, roi);
        }
        
        // Display the output image
        imshow(windowName, image);
        
        // Get the keyboard input and check if it's 'Esc'
        // 27 -> ASCII value of 'Esc' key
        ch = waitKey(30);
        if (ch == 27) {
            break;
        }
    }
    
    return 0;
}
