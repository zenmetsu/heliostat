#ifndef _SER_H_
#define _SER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include <unistd.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


void ser_get_details(std::ifstream& f, int &width, int &height, int &depth, int &count, size_t &s);

void ser_get_offset(uint64_t f, int w, int h, int d, uint64_t &o);
  
cv::Mat ser_get_frame(std::ifstream &serFile);

#endif // _SER_H_
