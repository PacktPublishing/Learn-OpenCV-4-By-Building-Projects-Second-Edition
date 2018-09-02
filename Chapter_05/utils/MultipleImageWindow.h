/**
 * Mutliple Image Window
 *
 * This class create a window with multiple images showed on it
 * in a grid with optional titles each one
 *
 * @author: David Millan Escriva
 * @email: david.millan@damiles.com
 *
 */

#ifndef MIW_h
#define MIW_h

#include <string>
#include <iostream>
using namespace std;

// OpenCV includes
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

class MultipleImageWindow
{
    public:
        /**
         * Constructor
         * Create new window with a max of cols*row images
         *
         * @param string window_title 
         * @param int cols number of cols
         * @param int rows number of rows
         * @param int flags see highgui window documentation
         */
        MultipleImageWindow(string window_title, int cols, int rows, int flags);

        /**
         * Add new image to stack of window
         * @param Mat image
         * @param string title caption of image to show
         * @return int position of image in stack
         */
        int addImage(string title, Mat image, bool render= false);

        /**
         * Remove a image from position n
         */
        void removeImage(int pos);

        /**
         * Render/redraw/update window
         */
        void render();

    private:
        int cols;
        int rows;
        int canvas_width;
        int canvas_height;
        string window_title;
        vector<string> titles;
        vector<Mat> images; 
        Mat canvas;
};


#endif
