// MOUSTACHE USING MOUTH DETECTOR

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>

#define CV_HAAR_SCALE_IMAGE 2

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    string faceCascadeName = argv[1];
    string mouthCascadeName = argv[2];
    
    CascadeClassifier faceCascade, mouthCascade;
    
    if( !faceCascade.load(faceCascadeName) )
    {
        cerr << "Error loading face cascade file. Exiting!" << endl;
        return -1;
    }

    if( !mouthCascade.load(mouthCascadeName) )
    {
        cerr << "Error loading mouth cascade file. Exiting!" << endl;
        return -1;
    }

    Mat mouthMask = imread(argv[3]);
    
    if ( !mouthMask.data )
    {
        cerr << "Error loading moustache image. Exiting!" << endl;
        return -1;
    }
    
    // Current frame
    Mat frame, frameGray;
    Mat frameROI, mouthMaskSmall;
    Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
    Mat maskedMouth, maskedFrame;
    
    // Create the capture object
    // 0 -> input arg that specifies it should take the input from the webcam
    VideoCapture cap(1);
    
    // If you cannot open the webcam, stop the execution!
    if( !cap.isOpened() )
        return -1;
    
    //create GUI windows
    namedWindow("Frame");
    
    // Scaling factor to resize the input frames from the webcam
    float scalingFactor = 0.75;
    
    vector<Rect> faces;
    
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
        //equalizeHist(frameGray, frameGray);
        
        // Detect faces
        faceCascade.detectMultiScale(frameGray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        
        vector<Point> centers;
        
        // Look for mouth in the face ROI
        for( auto& face:faces)
        {
            Mat faceROI = frameGray(face);
            vector<Rect> mouths;
            
            // In each face, detect mouths
            mouthCascade.detectMultiScale(faceROI, mouths, 1.1, 5, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
            
            for( auto& mouth:mouths )
            {
                Point center( face.x + mouth.x + int(mouth.width*0.5), face.y + mouth.y + int(mouth.height*0.5) );
                int radius = int( (mouth.width + mouth.height)*0.25 );
                //circle( frame, center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );
                
                // Overlay moustache
                int w = 1.8 * mouth.width;
                int h = mouth.height;
                int x = face.x + mouth.x - 0.2*w;
                int y = face.y + mouth.y + 0.65*h;
                
                frameROI = frame(Rect(x,y,w,h));
                resize(mouthMask, mouthMaskSmall, Size(w,h));
                cvtColor(mouthMaskSmall, grayMaskSmall, COLOR_BGR2GRAY);
                threshold(grayMaskSmall, grayMaskSmallThresh, 245, 255, THRESH_BINARY_INV);
                bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);
                bitwise_and(mouthMaskSmall, mouthMaskSmall, maskedMouth, grayMaskSmallThresh);
                bitwise_and(frameROI, frameROI, maskedFrame, grayMaskSmallThreshInv);
                add(maskedMouth, maskedFrame, frame(Rect(x,y,w,h)));
            }
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