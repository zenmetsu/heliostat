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
#include "telescope.h"


void calibrate_mount(std::ifstream& f, float &theta, float &decScale, float &raScale, bool &revRA, bool &revDec) {
	float x1,y1,x2,y2;
	float dx,dy;

	cv::Mat iframe = ser_get_frame(f);
	img_get_mass_center(iframe,x1,y1);
	slew_n(10000000);
	sleep(2);
	frame = ser_get_frame(f);
	img_get_mass_center(frame,x2,y2);
	dx=x2-x1;
	dy=y2-y1;

	theta=atan(dx/dy);
	if(dy < 0)
		revDec=true;
	decScale=sqrt(pow(dx,2)+pow(dy,2));
	slew_s(10000000);
	sleep(2);

	frame = ser_get_frame(f);
        img_get_mass_center(frame,x1,y1);
        slew_w(10000000);
        sleep(2);
        frame = ser_get_frame(f);
        img_get_mass_center(frame,x2,y2);
        dx=x2-x1;
        dy=y2-y1;
	raScale = sqrt(pow(dx,2)+pow(dy,2));
	if (dx < 0)
		revDec = true;
	slew_e(10000000);
	sleep(2);
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

void slew_n(int duration) {
  char temp[512];
  //sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_TIMED_GUIDE_NS.TIMED_GUIDE_N=%d\"", duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.5x=On\"");
  system((char *)temp);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_NORTH=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_NORTH=Off\"");
  system((char *)temp);
}

void slew_s(int duration) {
  char temp[512];
  //sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_TIMED_GUIDE_NS.TIMED_GUIDE_S=%d\"", duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.5x=On\"");
  system((char *)temp);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_SOUTH=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_NS.MOTION_SOUTH=Off\"");
  system((char *)temp);
}

void slew_w(int duration) {
  char temp[512];
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.5x=On\"");
  system((char *)temp);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_WEST=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_WEST=Off\"");
  //sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_TIMED_GUIDE_WE.TIMED_GUIDE_W=%d\"", duration);
  system((char *)temp);
}

void slew_e(int duration) {
  char temp[512];
  //sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_TIMED_GUIDE_WE.TIMED_GUIDE_E=%d\"", duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_SLEW_RATE.5x=On\"");
  system((char *)temp);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_EAST=On\"");
  system((char *)temp);
  usleep(duration);
  sprintf(temp, "/usr/bin/indi_setprop \"iOptron iEQ30.TELESCOPE_MOTION_WE.MOTION_EAST=Off\"");
  system((char *)temp);
}


