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
#include <math.h>

#include "ser.h"
#include "image_processing.h"
#include "telescope.h"

void guide_mount(int64_t decTime, int64_t raTime, bool reversedRA, bool reversedDec){
	if(reversedRA){
	  raTime *= -1;
	}
	if(reversedDec){
	  decTime *= -1;
	}

	if(decTime <= -1500000){
		slew_s(abs(decTime));
	}
	if(decTime > 1500000){
		slew_n(abs(decTime));
	}
	if(raTime <= -1500000){
		slew_w(abs(raTime));
	}
	if(raTime > 1500000){
		slew_e(abs(raTime));
	}
}

void calculate_correction(std::ifstream& f, float xDesired, float yDesired, float theta, float decScale, float raScale, int64_t& decTime, int64_t& raTime) {
        float x,y;
        
	cv::Mat frame = ser_get_frame(f);
        img_get_mass_center(frame,x,y);
	x = x - frame.cols/2;
	y = frame.rows/2 - y;

	float xRotated = x * cos(theta) + y * sin(theta);
	float yRotated = -x * sin(theta) + y * cos(theta);

	decTime = int64_t((yRotated - yDesired) / decScale);
	raTime  = int64_t((xDesired - xRotated) / raScale);
}

void get_desired_location(std::ifstream& f, float theta, float& xRotated, float& yRotated) {
        float x,y;
        
	cv::Mat frame = ser_get_frame(f);
        img_get_mass_center(frame,x,y);

	x = x - frame.cols/2;
	y = frame.rows/2 - y;

	xRotated = x * cos(theta) + y * sin(theta);
	yRotated = -x * sin(theta) + y * cos(theta);
}

void calibrate_mount(std::ifstream& f, float &theta, float &decScale, float &raScale, bool &revRA, bool &revDec) {
	float x1,y1,x2,y2;
	float dx,dy;
	int bp=0;
	uint64_t calibrationPulse = 8000000;

	cv::Mat frame = ser_get_frame(f);
	img_get_mass_center(frame,x1,y1);
	slew_n(calibrationPulse);
	sleep(4);
	frame = ser_get_frame(f);
	img_get_mass_center(frame,x2,y2);
	dx=x2-x1;
	dy=y2-y1;

	theta=atan(dx/dy);
	if(dy < 0)
		revDec=true;
	decScale=abs(sqrt(pow(dx,2)+pow(dy,2))/calibrationPulse);
	slew_s(calibrationPulse);
	sleep(4);

	slew_e(calibrationPulse);
	sleep(4);
	slew_w(calibrationPulse);
	sleep(4);
	frame = ser_get_frame(f);
        img_get_mass_center(frame,x1,y1);
        slew_w(calibrationPulse);
        sleep(4);
        frame = ser_get_frame(f);
        img_get_mass_center(frame,x2,y2);
        dx=x2-x1;
        dy=y2-y1;
	raScale = abs(sqrt(pow(dx,2)+pow(dy,2))/calibrationPulse);
	if (dx > 0)
		revRA = true;
	slew_e(calibrationPulse);
	sleep(4);
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void slew_n(uint64_t duration) {
  char temp[512];
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.3x=On\"");
  system((char *)temp);
  usleep(250000);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_NORTH=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_NORTH=Off\"");
  system((char *)temp);
}

void slew_s(uint64_t duration) {
  char temp[512];
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.3x=On\"");
  system((char *)temp);
  usleep(250000);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_SOUTH=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_SOUTH=Off\"");
  system((char *)temp);
}

void slew_w(uint64_t duration) {
  char temp[512];
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.3x=On\"");
  system((char *)temp);
  usleep(250000);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_WEST=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_WEST=Off\"");
  system((char *)temp);
}

void slew_e(uint64_t duration) {
  char temp[512];
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.3x=On\"");
  system((char *)temp);
  usleep(250000);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_EAST=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_EAST=Off\"");
  system((char *)temp);
}


