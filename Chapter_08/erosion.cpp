// EROSION 

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

// Function to perform erosion
Mat performErosion(Mat inputImage, int erosionElement, int erosionSize)
{
    Mat outputImage;
    int erosionType;
    
    if(erosionElement == 0)
        erosionType = MORPH_RECT;
    
    else if(erosionElement == 1)
        erosionType = MORPH_CROSS;
    
    else if(erosionElement == 2)
        erosionType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(erosionType, Size(2*erosionSize + 1, 2*erosionSize + 1), Point(erosionSize, erosionSize));
    
    // Erode the image using the structuring element
    erode(inputImage, outputImage, element);
    
    // Return the output image
    return outputImage;
}

// main function
int main(int argc, char** argv)
{
    Mat inputImage, outputImage;

    if(argc < 3)
    {
        cerr << "Insufficient input args. The format is:\n$ ./main image.jpg 5" << endl;
        return -1;
    }
    
    // Read the input image
    inputImage = imread(argv[1]);
    
    // Read the input value for the amount of erosion
    int erosionSize;
    istringstream iss(argv[2]);
    iss >> erosionSize;
    
    // Check the validity of the input image
    if(!inputImage.data)
    {
        cout << "Invalid input image. Exiting!" << endl;
        return -1;
    }
    
    int erosionElement = 0;

    // Create windows to display the input and output images
    namedWindow("Input image", WINDOW_AUTOSIZE);
    namedWindow("Output image after erosion", WINDOW_AUTOSIZE);
    
    // Erode the image
    outputImage = performErosion(inputImage, erosionElement, erosionSize);
    
    // Display the output image
    imshow("Input image", inputImage);
    imshow("Output image after erosion", outputImage);
    
    // Wait until the user hits a key on the keyboard
    waitKey(0);
    
    return 0;
}

