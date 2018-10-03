// NOSE DETECTOR

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
    string noseCascadeName = argv[2];
    CascadeClassifier faceCascade, noseCascade;
    
    if( !faceCascade.load(faceCascadeName) )
    {
        cerr << "Error loading face cascade file. Exiting!" << endl;
        return -1;
    }

    if( !noseCascade.load(noseCascadeName) )
    {
        cerr << "Error loading nose cascade file. Exiting!" << endl;
        return -1;
    }
    
    Mat noseMask = imread(argv[3]);
    
    if ( !noseMask.data )
    {
        cerr << "Error loading nose mask image. Exiting!" << endl;
        return -1;
    }

    // Current frame
    Mat frame, frameGray;
    Mat frameROI, noseMaskSmall;
    Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
    Mat maskedNose, maskedFrame;
    
    char ch;
    
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
        equalizeHist(frameGray, frameGray);
        
        // Detect faces
        faceCascade.detectMultiScale(frameGray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        
        // Draw green circles around the nose
        for(int i = 0; i < faces.size(); i++)
        {
            Mat faceROI = frameGray(faces[i]);
            vector<Rect> noses;
            
            // In each face, detect the nose
            noseCascade.detectMultiScale(faceROI, noses, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
            
            for(int j = 0; j < noses.size(); j++)
            {
                Point center( faces[i].x + noses[j].x + int(noses[j].width*0.5), faces[i].y + noses[j].y + int(noses[j].height*0.5) );
                int radius = int( (noses[j].width + noses[j].height)*0.25 );
                //circle( frame, center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );
                
                for(int j = 0; j < noses.size(); j++)
                {
                    Point center( faces[i].x + noses[j].x + int(noses[j].width*0.5), faces[i].y + noses[j].y + int(noses[j].height*0.5) );
                    int radius = int( (noses[j].width + noses[j].height)*0.25 );
                    //circle( frame, center, radius, Scalar( 0, 255, 0 ), 4, 8, 0 );
                    
                    // Overlay moustache
                    int w = 1.3 * noses[j].width;
                    int h = 1.7 * noses[j].height;
                    int x = faces[i].x + noses[j].x - 0.1*w;
                    int y = faces[i].y + noses[j].y - 0.3*h;
                    
                    frameROI = frame(Rect(x,y,w,h));
                    resize(noseMask, noseMaskSmall, Size(w,h));
                    cvtColor(noseMaskSmall, grayMaskSmall, COLOR_BGR2GRAY);
                    threshold(grayMaskSmall, grayMaskSmallThresh, 250, 255, THRESH_BINARY_INV);
                    bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);
                    bitwise_and(noseMaskSmall, noseMaskSmall, maskedNose, grayMaskSmallThresh);
                    bitwise_and(frameROI, frameROI, maskedFrame, grayMaskSmallThreshInv);
                    add(maskedNose, maskedFrame, frame(Rect(x,y,w,h)));
                }
            }
        }
        
        // Show the current frame
        imshow("Frame", frame);
        
        // Get the keyboard input and check if it's 'Esc'
        // 27 -> ASCII value of 'Esc' key
        ch = waitKey( 30 );
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