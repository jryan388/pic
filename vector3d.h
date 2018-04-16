#ifndef VECTOR3D_H_INCLUDED__
#define VECTOR3D_H_INCLUDED__

#include <string>
#include <iostream>

class Vector3D {
 private:
  double x;
  double y;
  double z;

 public:

  Vector3D();

  Vector3D(double x, double y, double z);

  Vector3D(double theta, double phi);

  double getX() { return x; };
  double getY() { return y; };
  double getZ() { return z; };

  Vector3D operator + (Vector3D rhs);
  Vector3D operator - (Vector3D rhs);
  Vector3D operator * (double rhs);
  Vector3D operator / (double rhs);
  double operator * (Vector3D rhs);





  double dot(Vector3D);
  Vector3D cross(Vector3D);
  double length();
  Vector3D unit();
  Vector3D rotate(double theta, double phi);

  Vector3D left90();
  Vector3D right90();
  Vector3D up90();
  Vector3D down90();
  
  double getTheta();  
  double getPhi();
  
  Vector3D refl(Vector3D norm);


  Vector3D toCartesian(double, double, double);
  void print();
};

#endif
