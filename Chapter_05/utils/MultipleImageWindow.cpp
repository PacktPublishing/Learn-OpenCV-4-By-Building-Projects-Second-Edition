#include "MultipleImageWindow.h"

MultipleImageWindow::MultipleImageWindow(string window_title, int cols, int rows, int flags)
{
    this->window_title= window_title;
    this->cols= cols;
    this->rows= rows;
    namedWindow(window_title, flags);
    // ToDo: detect resolution of desktop and show fullresolution canvas
    this->canvas_width= 1200;
    this->canvas_height= 700;
    this->canvas= Mat(this->canvas_height, this->canvas_width, CV_8UC3);     
    imshow(this->window_title, this->canvas);
}

int MultipleImageWindow::addImage(string title, Mat image, bool render)
{
    this->titles.push_back(title);
    this->images.push_back(image);
    if(render)
        this->render();
    return this->images.size()-1;
}

void MultipleImageWindow::removeImage(int pos)
{
    this->titles.erase(this->titles.begin()+pos);
    this->images.erase(this->images.begin()+pos);
}

void MultipleImageWindow::render()
{
    // Clean our canvas
    this->canvas.setTo( Scalar(20,20,20) );
    // width and height of cell. add 10 px of padding between images
    int cell_width= (canvas_width/cols);
    int cell_height= (canvas_height/rows);
    int margin= 10;
    int max_images=(this->images.size()>cols*rows)?cols*rows:this->images.size();
    int i=0;
    vector<string>::iterator titles_it= this->titles.begin();
    for(vector<Mat>::iterator it= this->images.begin(); it!= this->images.end(); ++it)
    {
        string title= *titles_it;
        int cell_x= (cell_width)*((i)%cols);
        int cell_y= (cell_height)*floor((i)/(float)cols);
        Rect mask(cell_x, cell_y, cell_width, cell_height);
        // Draw a rectangle for each cell mat 
        rectangle(canvas, Rect(cell_x, cell_y, cell_width, cell_height), Scalar(200,200,200), 1);
        //For each cell draw an image if exists
        Mat cell(this->canvas, mask);
        // resize image to cell size
        Mat resized;
        double cell_aspect= (double)cell_width/(double)cell_height;
        Mat img= *it;
        double img_aspect= (double)img.cols/(double)img.rows;
        double f=(cell_aspect<img_aspect)?(double)cell_width/(double)img.cols:(double)cell_height/(double)img.rows;
        resize(img, resized, Size(0,0), f, f);
        if(resized.channels()==1){
            cvtColor(resized, resized, COLOR_GRAY2BGR); 
        }

        // Assign the image
        Mat sub_cell(this->canvas, Rect(cell_x,cell_y,resized.cols, resized.rows));
        resized.copyTo(sub_cell);
        putText(cell, title.c_str(), Point(20,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(200,0,0), 1, LINE_AA);
        i++;
        ++titles_it;
        if(i==max_images)
            break;
    }

    // show image
    imshow(this->window_title, this->canvas);
}

