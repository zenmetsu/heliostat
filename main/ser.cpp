#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include "ser.h"

int serHeaderSize = 178;

void ser_get_details(std::ifstream &f, int &width, int &height, int &depth, int &count) {
  f.seekg(0, std::ios::end);
  size_t s = f.tellg();
  std::cout << "Size: " << s << " ";
  f.seekg(26);
  f.read((char*)&width,  sizeof(width));
  f.read((char*)&height, sizeof(height));
  f.read((char*)&depth,  sizeof(depth));
  f.read((char*)&count,  sizeof(count));
}

void ser_get_offset(uint64_t f, int w, int h, int d, uint64_t &o) {
  o = serHeaderSize + (f - 1)*(w * h * (d / 8));
  std::cout << "Offset: " << o << " ";
}
  
void ser_get_frame(std::ifstream &f, uint64_t o, uint64_t c, std::vector<uint16_t> &v) {
  f.seekg(o);
  f.read(reinterpret_cast<char*>(v.data()), c);
}
