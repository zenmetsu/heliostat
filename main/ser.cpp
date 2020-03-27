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

void ser_get_details(std::ifstream& f, int& width, int& height, int &depth, int &count, size_t &s) {
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
  
cv::Mat ser_get_frame(std::ifstream& serFile){
	uint64_t currentFrame     = 0;
	int iWidth,iHeight,iDepth = 0;
	uint64_t offset,count     = 0;
	size_t serLength;
	int maxBright             = 0;
	

	//ser_get_details(serFile, iWidth, iHeight, iDepth, count, serLength);

	serFile.seekg(0, std::ios::end);
	serLength = serFile.tellg();
 	serFile.seekg(26);
 	serFile.read((char*)&iWidth,  sizeof(iWidth));
 	serFile.read((char*)&iHeight, sizeof(iHeight));
	serFile.read((char*)&iDepth,  sizeof(iDepth));


	std::vector<uint16_t> imageArray(iWidth*iHeight);
	currentFrame = (serLength - 178) / (uint64_t)(iWidth * iHeight * (iDepth / 8));
	
	std::cout << "Frame: " << currentFrame << "\n";
	count = iWidth * iHeight;
        //currentFrame = 1;
	ser_get_offset(currentFrame, iWidth, iHeight, iDepth, offset);
	std::cout << "Offset: " << offset << "\n";
	std::cout << "Width: " << iWidth << "\n";
	std::cout << "Height: " << iHeight << "\n";
	std::cout << "Count: " << count << "\n";
	serFile.seekg(offset);

	if (iDepth == 8){
		for(uint64_t i=0;i<count;i++){
			char buf[1];
			serFile.read(buf, 1);
			imageArray.at(i) = (uint16_t)buf[0]*256;
			if (buf[0] > maxBright)
				maxBright = buf[0];
		}
		std::cout << "Max Brightness: " << maxBright << "\n";
	} else {
		serFile.read(reinterpret_cast<char*>(imageArray.data()), count * 2);
	}
        //cv::Mat src(iHeight, iWidth, CV_16UC1, imageArray.data());
	//cv::namedWindow( "SOURCE", CV_WINDOW_NORMAL);
	//cv::imshow("SOURCE",src);
	//cv::waitKey(0);
	//std::cout << "imageArray Size: " << imageArray.size();
	return cv::Mat(iHeight, iWidth, CV_16UC1, imageArray.data()).clone();
	//return cv::Mat(iHeight, iWidth, CV_16UC1, imageArray.data());
}
