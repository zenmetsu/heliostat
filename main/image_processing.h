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

void process_frame(std::vector<uint16_t> &v, int h, int w, float &x, float &y);

void img_get_mass_center(std::vector<uint16_t> &v,int h, int w, float &x,float &y);

#endif // _IMAGE_PROCESSING_H_
