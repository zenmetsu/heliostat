#ifndef _SER_H_
#define _SER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>

void ser_get_details(std::ifstream &f, int &width, int &height, int &depth, int &count);

void ser_get_offset(uint64_t f, int w, int h, int d, uint64_t &o);
  
void ser_get_frame(std::ifstream &f, uint64_t o, uint64_t c, std::vector<uint16_t> &v);

#endif // _SER_H_
