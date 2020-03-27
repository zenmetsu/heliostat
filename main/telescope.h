#ifndef _TELESCOPE_H_
#define _TELESCOPE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include <getopt.h>
#include <memory>
#include <stdexcept>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "ser.h"
#include "image_processing.h"

void slew_n(int duration);
void slew_s(int duration);
void slew_w(int duration);
void slew_e(int duration);
void calibrate_mount(std::ifstream& f, float &theta, float &decScale, float &raScale, bool &revRA, bool &revDec);
std::string exec(const char* cmd);  

#endif // _TELESCOPE_H_
