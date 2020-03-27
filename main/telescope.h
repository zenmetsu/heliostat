#ifndef _TELESCOPE_H_
#define _TELESCOPE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <getopt.h>
#include <memory>
#include <stdexcept>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "ser.h"
#include "image_processing.h"

void slew_n(uint64_t duration);
void slew_s(uint64_t duration);
void slew_w(uint64_t duration);
void slew_e(uint64_t duration);
void guide_mount(int64_t decTime, int64_t raTime, bool reversedRA, bool reversedDec);
void calibrate_mount(std::ifstream& f, float &theta, float &decScale, float &raScale, bool &revRA, bool &revDec);
void calculate_correction(std::ifstream& f, float xCurrent, float yCurrent, float theta, float decScale, float raScale, int64_t& decTime, int64_t& raTime);
void get_desired_location(std::ifstream& f, float theta, float& xRotated, float& yRotated);
std::string exec(const char* cmd);  

#endif // _TELESCOPE_H_
