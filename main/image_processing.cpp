#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include "image_processing.h"

using namespace cv;
Mat src_gray;
int thresh           = 55;
int max_thresh       = 255;
RNG rng(1776);

/*
void process_frame(std::vector<uint16_t> &v, int h, int w, float &x, float &y) {

	//std::cout << "Vector Size : " << v.size() << "\n";
        // create Mats
        Mat src(h, w, CV_16UC1, v.data());
        Mat canny_output;
        std::vector<std::vector<Point> > contours;
        std::vector<Vec4i> hierarchy;

        // create window
        char const *source_window = "Source";
        //namedWindow( source_window, CV_WINDOW_NORMAL );
        //imshow( source_window, src );
        // blur the source data
        blur(src, src, Size(10,10));
        //waitKey(0);
        // convert to 8bit monochrome
        src.convertTo(src_gray, CV_8U, 0.00390625);

        // binarize the working data
        threshold(src_gray, src_gray, 128,255,THRESH_BINARY);
        //imshow( source_window, src_gray );
        // detect edges using canny
        Canny( src_gray, canny_output, thresh, thresh*2, 3 );

        // find contours
        findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        // get the moments
        std::vector<Moments> mu(contours.size() );
        for( int i = 0; i < contours.size(); i++ ) {
          mu[i] = moments( contours[i], false );
        }

        // get the mass centers:
	x = 0;
	y = 0;
        std::vector<Point2f> mc( contours.size() );
        for( int i = 0; i < contours.size(); i++ ) {
          mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
          x=mc[i].x;
	  y=mc[i].y;
        }
	Point2f mean(x,y);
        // Draw Contours
        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        Scalar color = Scalar( 255, 255, 255 );
        Scalar mColor = Scalar( 0, 0, 255 );
        for( int i = 0; i< contours.size(); i++ )
          {
	    //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
            //circle( drawing, mc[i], 4, color, -1, 8, 0 );
          }
        circle( drawing, mean, 4, mColor, -1, 8, 0 );

        // display contours
        //namedWindow ( "Contours", CV_WINDOW_NORMAL );
        //imshow("Contours", drawing);
        //waitKey(0);
        // calculate single mass center
        std::cout << "Mass Center: " << mean  << "\n";
}
*/

void img_get_mass_center(cv::Mat src, float &x,float &y){
	cv::Mat canny_output;
	std::vector<std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	cv::blur(src, src, Size(10,10));
	src.convertTo(src_gray, CV_8U, 0.00390625);
	cv::threshold(src_gray, src_gray, 128,255,THRESH_BINARY);

	cv::Canny( src_gray, canny_output, thresh, thresh*2, 3 );
	cv::findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	std::vector<Moments> mu(contours.size() );
        for( int i = 0; i < contours.size(); i++ ) {
          mu[i] = moments( contours[i], false );
        }

        // get the mass centers:
        x = 0;
        y = 0;
        std::vector<Point2f> mc( contours.size() );
        for( int i = 0; i < contours.size(); i++ ) {
          mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
          x=mc[i].x;
          y=mc[i].y;
        }
        Point2f mean(x,y);
        std::cout << "Mass Center: " << mean  << "\n";

}
