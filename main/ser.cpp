#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include "ser.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


int serHeaderSize = 178;

void ser_get_details(std::ifstream &f, int& width, int& height, int &depth, int &count, size_t &s) {
  f.seekg(0, std::ios::end);
  s = f.tellg();
  f.seekg(26);
  f.read((char*)&width,  sizeof(width));
  f.read((char*)&height, sizeof(height));
  f.read((char*)&depth,  sizeof(depth));
  f.read((char*)&count,  sizeof(count));
}

void ser_get_offset(uint64_t f, int w, int h, int d, uint64_t &o) {
  o = serHeaderSize + (f - 1)*(w * h * (d / 8));
}
  
cv::Mat ser_get_frame(std::ifstream &serFile){
	std::vector<uint16_t> imageArray;
	uint64_t currentFrame     = 0;
	int iWidth,iHeight,iDepth = 0;
	int count                 = 0;
	uint64_t offset           = 0;
	size_t serLength;

	ser_get_details(serFile, iWidth, iHeight, iDepth, count, serLength);
	currentFrame = (serLength - 178) / (uint64_t)(iWidth * iHeight * (iDepth / 8));
	count = iWidth * iDepth;

	ser_get_offset(currentFrame, iWidth, iHeight, iDepth, offset);
	serFile.seekg(offset);

	if (iDepth == 8){
		for(uint64_t i=0;i<count;i++){
			char buf[1];
			serFile.read(buf, 1);
			imageArray.at(i) = (uint16_t)buf[0]*256;
		}
	} else {
		serFile.read(reinterpret_cast<char*>(imageArray.data()), count * 2);
	}
	
	cv::Mat imageFrame(iHeight, iWidth, CV_16UC1, imageArray.data());
	return imageFrame;
}
