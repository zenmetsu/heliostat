#ifndef _IMAGE_PROCESSING_H_
#define _IMAGE_PROCESSING_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>


void img_get_mass_center(cv::Mat src, float &x,float &y);

#endif // _IMAGE_PROCESSING_H_
