#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include <getopt.h>


#include "ser.h"
#include "image_processing.h"

std::string serFile  = "";

static void show_usage() {
	std::cout <<
	        "Usage: heliostat [OPTION]... --file [SERFILE]\n"
                "Monitor SERFILE and generate autoguiding output\n\n"

		"-f, --file <fname>	.ser file to monitor\n"
		"-h, --help		Show this message\n";
	exit(1);
}

void process_args(int argc, char** argv) {
	const char* const short_opts = "f:h";
	const option long_opts[] = {
		{"file", required_argument, nullptr, 'f'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, no_argument, nullptr, 0}
	};
	while (true) {
		const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

		if (-1 == opt)
			break;

		switch (opt) {
			case 'f':
				serFile = std::string(optarg);
				break;

			case 'h': // -h or --help
			case '?': // User has a confused
			default:
				show_usage();
				break;
			}
	}
}



int main(int argc, char* argv[])
{
  std::ifstream inStream;
  int imageWidth       = 0;
  int imageHeight      = 0;
  int imageDepth       = 0;
  int imageCount       = 0;
  uint64_t frameSize   = 0;
  uint64_t frameToGrab = 0;
  uint64_t frameOffset = 0;

  process_args(argc, argv);
	if ("" == serFile) {
		std::cerr << "heliostat: missing file operand\n";
		std::cerr << "Try 'heliostat --help' for more information.\n";
		exit(1);
	}

  inStream.open( serFile, std::ios::in|std::ios::binary );
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
