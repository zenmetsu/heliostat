# Heliostat

Heliostat is a autoguiding application for solar, lunar, and planetary imaging.

The project's page is located at [Heliostat](https://github.com/zenmetsu/heliostat).

TODO:

* Commandline/argument parsing
* Filtering
* INDI integration
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
