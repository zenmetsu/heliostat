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
int thresh           = 25;
int max_thresh       = 255;


void process_frame(std::vector<uint16_t> &v, int h, int w) {
        // create Mats
        Mat src(h, w, CV_16UC1, v.data());
        Mat canny_output;
        std::vector<std::vector<Point> > contours;
        std::vector<Vec4i> hierarchy;

        // create window
        char const *source_window = "Source";
        namedWindow( source_window, CV_WINDOW_NORMAL );
        imshow( source_window, src );

        // blur the source data
        blur(src, src, Size(5,5));

        // convert to 8bit monochrome
        src.convertTo(src_gray, CV_8U, 0.00390625);

        // binarize the working data
        threshold(src_gray, src_gray, 10,255,THRESH_BINARY);

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
        std::vector<Point2f> mc( contours.size() );
        for( int i = 0; i < contours.size(); i++ ) {
          mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
        }

        // calculate a single mass center
        cv::Mat mean_;
        cv::reduce(mc, mean_, 01, CV_REDUCE_AVG);
        cv::Point2f mean(mean_.at<float>(0.0), mean_.at<float>(0,1));

        // Draw Contours
        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        Scalar color = Scalar( 255, 255, 255 );
        Scalar mColor = Scalar( 0, 0, 255 );
        for( int i = 0; i< contours.size(); i++ )
          {
            drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
            circle( drawing, mc[i], 4, color, -1, 8, 0 );
          }
        circle( drawing, mean, 4, mColor, -1, 8, 0 );

        // display contours
        namedWindow ( "Contours", CV_WINDOW_NORMAL );
        imshow("Contours", drawing);

        // calculate single mass center
        std::cout << "Mass Center: " << mean  << "\n";
        waitKey(0);
}
