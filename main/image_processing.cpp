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

void img_get_mass_center(cv::Mat src, float &x,float &y){
	int bp               = 0;
	cv::Mat src_gray;
	int thresh           = 55;
	int max_thresh       = 255;
	RNG rng(1776);
	std::cout << "Image Width: " << src.cols << "," << src.rows << "\n";

	//namedWindow( "Source", WINDOW_NORMAL );
	//imshow( "Source", src );
	//waitKey(0);

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
