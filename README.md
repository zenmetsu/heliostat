# Heliostat

Heliostat is a autoguiding application for solar, lunar, and planetary imaging.

The project's page is located at [Heliostat](https://github.com/zenmetsu/heliostat).

Status:
* Currently application compiles without warning
* Application will parse commandline and accept a file operand
* Application will calibrate the mount and determine
	* Field rotation of camera
	* RA/DEC correction directions and magnitudes
* Application steps through each frame in the .ser where it
	* Displays the raw data from the camera
	* Displays the detected contours and center of mass
	* Waits for user to press a key to step to the next image
	* Outputs the detected center of mass coordinates to the console

TODO:

* ~~Commandline/argument parsing~~
* Filtering
* ~~INDI integration~~
	* Currently application makes system calls to indi_getprop and indi_setprop
	* Will need to code these in natively
	* Need to parse getprop to allow user to interactively select mount by name
* Field testing

# License
[LGPL v.3.0](LICENSE)

# Requirements

* A C++11 compliant compiler with complete support for C++11 regex (e.g., GCC 4.9 meets the minimum feature set required to build the package)
* CMake build system
* Currently the project only compiles on Linux

# Dependencies

* libindi
* libopencv

# Build

The project is using CMake as a build system. To build and install the package, execute the following commands in the root directory of the project:

        cmake .
        make
        sudo make install

If your default compiler does not meet the minimum feature set required to build the package, you may specify alternative compiler as follows:

        CC=gcc-4.9 CXX=g++-4.9 cmake .
        make
        sudo make install

In default configuration, the package will be installed with prefix `/usr`. If you want to change the prefix, you may specify it as follows:

        cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/local .
        make
        sudo make install

For more information see documentation available on official [CMake site](http://www.cmake.org/documentation/).

# Docs

* To be completed

# Examples

* To be completed
