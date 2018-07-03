#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
	"{help h usage ? | | print this message}"
    "{@sample |0 | Sample number to show}"
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

	int sample= parser.get<int>(0);

	// Check if params are correctly parsed in his variables
	if (!parser.check())
	{
	    parser.printErrors();
	    return 0;
	}

	switch(sample)
	{
		case 0:
		{	cout << "Sample 0, Mat zeros" << endl;
			Mat m= Mat::zeros(5,5, CV_32F);
			cout << m << endl;
			break;
		}
		case 1:
		{	cout << "Sample 0, Mat ones" << endl;
			Mat m= Mat::ones(5,5, CV_32F);
			cout << m << endl;
			break;
		}
		case 2:
		{	cout << "Sample 0, Mat eye" << endl;
			Mat m= Mat::eye(5,5, CV_32F);
			cout << m << endl;

			Mat a= Mat::eye(Size(3,2), CV_32F);
			Mat b= Mat::ones(Size(3,2), CV_32F);
			Mat c= a+b;
			Mat d= a-b;
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;
			cout << d << endl;
			break;
		}
		case 3:
		{	cout << "Sample 0, Mat operations:" << endl;
			Mat m0= Mat::eye(3,3, CV_32F);
			m0=m0+Mat::ones(3,3, CV_32F);
			Mat m1= Mat::eye(2,3, CV_32F);
			Mat m2= Mat::ones(3,2, CV_32F);

			cout << "\nm0\n" << m0 << endl;
			cout << "\nm1\n" << m1 << endl;
			cout << "\nm2\n" << m2 << endl;
			
			cout << "\nm1.*2\n" << m1*2 << endl;
			cout << "\n(m1+2).*(m1+3)\n" << (m1+1).mul(m1+3) << endl;
			cout << "\nm1*m2\n" << m1*m2 << endl;
			cout << "\nt(m2)\n" << m2.t() << endl;
			cout << "\ninv(m0)\n" << m0.inv() << endl;
			break;
		}
		case 4:
		{
			Mat image= imread("../lena.jpg", 0);
			int myRow=511;
			int myCol=511;
			int val=*(image.data+myRow*image.cols*image.channels()+ myCol);
			cout << "Pixel value: " << val << endl;
			imshow("Lena", image);
			waitKey(0);
			break;
		}
		case 5:
		{
			Mat image= imread("../lena.jpg");
			int myRow=511;
			int myCol=511;
			int B=*(image.data+myRow*image.cols*image.channels()+ myCol + 0);
			int G=*(image.data+myRow*image.cols*image.channels()+ myCol + 1);
			int R=*(image.data+myRow*image.cols*image.channels()+ myCol + 2);
			cout << "Pixel value (B,G,R): (" << B << "," << G << "," << R << ")" << endl;
			imshow("Lena", image);
			waitKey(0);
			break;
		}
		case 6:
		{
			Vec<double,19> myVector;
			for(int i=0; i<19; i++){
				myVector[i]= i;
			}
			cout << myVector << endl;

		}
	}

	return 0;

}