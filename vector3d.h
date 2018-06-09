#ifndef VECTOR3D_H_INCLUDED__
#define VECTOR3D_H_INCLUDED__

#include <string>
#include <iostream>

struct Vector3D {
  double x;
  double y;
  double z;

Vector3D(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}
  
  Vector3D operator + (Vector3D rhs);
  Vector3D operator - (Vector3D rhs);
  Vector3D operator * (double rhs);
  Vector3D operator / (double rhs);

  void print();
};

#endif
