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

#include "image_processing.h"
#include "ser.h"
#include "telescope.h"

std::string serFile  = "";

static void show_usage();
void process_args(int argc, char** argv);

int main(int argc, char* argv[]) {
  std::ifstream inStream;
  size_t serSize         = 0;
  int imageWidth         = 0;
  int imageHeight        = 0;
  int imageDepth         = 0;
  int imageCount         = 0;
  uint64_t frameSize     = 0;
  uint64_t frameToGrab   = 0;
  uint64_t prevFrame     = 0;
  uint64_t frameOffset   = 0;
  float xCm,yCm          = 0;
  float theta            = 0;
  float decScale,raScale = 0;
  bool reversedRA        = false;
  bool reversedDec       = false;


  process_args(argc, argv);
	if ("" == serFile) {
		std::cerr << "heliostat: missing file operand\n";
		std::cerr << "Try 'heliostat --help' for more information.\n";
		exit(1);
	}

  inStream.open( serFile, std::ios::in|std::ios::binary );
  while( true ) {
	calibrate_mount(inStream, theta, decScale, raScale, reversedRA, reversedDec);
	std::cout << theta << "," << decScale << "," << raScale << "\n";

	sleep(30);
      }
}

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
