#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
	"{help h usage ? | | print this message}"
    "{@image | | image to load}"
};


int main( int argc, const char** argv )
{
	CommandLineParser parser(argc, argv, keys);
    parser.about("Chapter 2. v1.0.0");
    //If requires help show
    if (parser.has("help"))
	{
	    parser.printMessage();
	    return 0;
	}

	string image= parser.get<string>(0);

	// Check if params are correctly parsed in his variables
	if (!parser.check())
	{
	    parser.printErrors();
	    return 0;
	}



}