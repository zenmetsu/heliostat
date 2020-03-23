#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>

#include "ser.h"
#include "image_processing.h"

int main()
{
  std::ifstream inStream;
  int imageWidth       = 0;
  int imageHeight      = 0;
  int imageDepth       = 0;
  int imageCount       = 0;
  uint64_t frameSize   = 0;
  uint64_t frameToGrab = 0;
  uint64_t frameOffset = 0;

  inStream.open( "14_56_58.ser", std::ios::in|std::ios::binary );
  frameToGrab = 0; // temporary debugging to grab first frame
  while( true ) {
        frameToGrab++;

	// retrieve details from .ser header
        ser_get_details(inStream, imageWidth, imageHeight, imageDepth, imageCount);

	// find offset for current frame
	ser_get_offset(frameToGrab, imageWidth, imageHeight, imageDepth, frameOffset);
        std::cout << "Offset: " << frameOffset << " "; 

        // retrieve frame from .ser
        std::vector<uint16_t> array(imageHeight*imageWidth);
        frameSize = imageHeight*imageWidth*(imageDepth/8);
	ser_get_frame(inStream, frameOffset, frameSize, array);

        // process current frame
	process_frame(array, imageHeight, imageWidth);
      }
}
