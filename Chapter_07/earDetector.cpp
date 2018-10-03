// EAR DETECTION

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    string leftEarCascadeName = argv[1];
    string rightEarCascadeName = argv[2];
    CascadeClassifier leftEarCascade, rightEarCascade;
    
    if( !leftEarCascade.load(leftEarCascadeName) )
    {
        cerr << "Error loading left ear cascade file. Exiting!" << endl;
        return -1;
    }
    
    if( !rightEarCascade.load(rightEarCascadeName) )
    {
        cerr << "Error loading right ear cascade file. Exiting!" << endl;
        return -1;
    }
    
    // Current frame
    Mat frame, frameGray;
    
    // Create the capture object
    // 0 -> input arg that specifies it should take the input from the webcam
    VideoCapture cap(0);
    
    // If you cannot open the webcam, stop the execution!
    if( !cap.isOpened() )
        return -1;
    
    //create GUI windows
    namedWindow("Frame");
    
    // Scaling factor to resize the input frames from the webcam
    float scalingFactor = 0.75;
    
    vector<Rect> leftEars, rightEars;
    
    // Iterate until the user presses the Esc key
    while(true)
    {
        // Capture the current frame
        cap >> frame;
        
        // Resize the frame
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);
        
        // Convert to grayscale
        cvtColor(frame, frameGray, COLOR_BGR2GRAY);
        
        // Equalize the histogram
        equalizeHist(frameGray, frameGray);
        
        // Detect left ear
        leftEarCascade.detectMultiScale(frameGray, leftEars, 1.1, 2, 0|2, Size(30, 30) );
        
        // Detect right ear
        rightEarCascade.detectMultiScale(frameGray, rightEars, 1.1, 2, 0|2, Size(30, 30) );
        
        // Draw green rectangle around the left ear
        for( auto& leftEar: leftEars)
        {
            Rect leftEarRect(leftEar.x, leftEar.y, leftEar.width, leftEar.height);
            rectangle(frame, leftEarRect, Scalar(0,255,0), 4);
        }
        
        // Draw green rectangle around the right ear
        for( auto& rightEar: rightEars )
        {
            Rect rightEarRect(rightEar.x, rightEar.y, rightEar.width, rightEar.height);
            rectangle(frame, rightEarRect, Scalar(0,255,0), 4);
        }
        
        // Show the current frame
        imshow("Frame", frame);
        
        // Get the keyboard input and check if it's 'Esc'
        // 27 -> ASCII value of 'Esc' key
        auto ch = waitKey( 30 );
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