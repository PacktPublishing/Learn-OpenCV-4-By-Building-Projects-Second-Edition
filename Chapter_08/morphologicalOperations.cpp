// MORPHOLOGICAL OPERATIONS

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function to perform morphological opening
Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply morphological opening to the image using the structuring element
    erode(inputImage, tempImage, element);
    dilate(tempImage, outputImage, element);
    
    // Return the output image
    return outputImage;
}

// Function to perform morphological closing
Mat performClosing(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply morphological opening to the image using the structuring element
    dilate(inputImage, tempImage, element);
    erode(tempImage, outputImage, element);
    
    // Return the output image
    return outputImage;
}

// Function to perform morphological gradient
Mat performMorphologicalGradient(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage1, tempImage2;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply morphological gradient to the image using the structuring element
    dilate(inputImage, tempImage1, element);
    erode(inputImage, tempImage2, element);
    
    // Return the output image
    return tempImage1 - tempImage2;
}

// Function to perform top hat operation
Mat performTopHat(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply top hat operation to the image using the structuring element
    outputImage = inputImage - performOpening(inputImage, morphologyElement, morphologySize);
    
    // Return the output image
    return outputImage;
}

// Function to perform black hat operation
Mat performBlackHat(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply black hat operation to the image using the structuring element
    outputImage = performClosing(inputImage, morphologyElement, morphologySize) - inputImage;
    
    // Return the output image
    return outputImage;
}

// main function
int main(int argc, char** argv)
{
    Mat inputImage, openingOutputImage, closingOutputImage, gradientOutputImage, tophatOutputImage, blackhatOutputImage;
    
    if(argc < 3)
    {
        cerr << "Insufficient input args. The format is:\n$ ./main image.jpg 5" << endl;
        return -1;
    }
    
    // Read the input image
    inputImage = imread(argv[1]);
    
    // Read the input value for the amount of erosion
    int morphologySize;
    istringstream iss(argv[2]);
    iss >> morphologySize;
    
    // Check the validity of the input image
    if(!inputImage.data)
    {
        cout << "Invalid input image. Exiting!" << endl;
        return -1;
    }
    
    int morphologyElement = 0;

    // Create windows to display the input and output images
    namedWindow("Input image", WINDOW_AUTOSIZE);
    namedWindow("Output image after opening", WINDOW_AUTOSIZE);
    namedWindow("Output image after closing", WINDOW_AUTOSIZE);
    namedWindow("Output image after morphological gradient", WINDOW_AUTOSIZE);
    namedWindow("Output image after top hat", WINDOW_AUTOSIZE);
    namedWindow("Output image after black hat", WINDOW_AUTOSIZE);
    
    // Apply morphological opening
    openingOutputImage = performOpening(inputImage, morphologyElement, morphologySize);
    
    // Apply morphological closing
    closingOutputImage = performClosing(inputImage, morphologyElement, morphologySize);
    
    // Apply morphological gradient
    gradientOutputImage = performMorphologicalGradient(inputImage, morphologyElement, morphologySize);
    
    // Apply top hat operation
    tophatOutputImage = performTopHat(inputImage, morphologyElement, morphologySize);
    
    // Apply black hat operation
    blackhatOutputImage = performBlackHat(inputImage, morphologyElement, morphologySize);
    
    // Display the output image
    imshow("Input image", inputImage);
    imshow("Output image after opening", openingOutputImage);
    imshow("Output image after closing", closingOutputImage);
    imshow("Output image after morphological gradient", gradientOutputImage);
    imshow("Output image after top hat", tophatOutputImage);
    imshow("Output image after black hat", blackhatOutputImage);
    
    // Wait until the user hits a key on the keyboard
    waitKey(0);
    
    return 0;
}

