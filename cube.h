#ifndef CUBE_H_INCLUDED__
#define CUBE_H_INCLUDED__

#include <string>
#include <iostream>

struct Cube {
  double x1;
  double y1;
  double z1;
  double x2;
  double y2;
  double z2;

Cube(double x1_ = 0, double y1_ = 0, double z1_ = 0, double x2_ = 0, double y2_ = 0, double z2_ = 0) : x1(x1_), y1(y1_), z1(z1_), x2(x2_), y2(y2_), z2(z2_) {}
  
};

#endif
