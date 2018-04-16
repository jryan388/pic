#include "vector3d.h"
#include <cmath>
#include <string>
#include <iostream>

Vector3D::Vector3D() {
  x = 1;
  y = 1;
  z = 1;
}

Vector3D::Vector3D(double initX, double initY, double initZ) {
  x = initX;
  y = initY;
  z = initZ;
}

Vector3D::Vector3D(double theta, double phi) {
  x = sin(phi)*cos(theta);
  y = sin(phi)*sin(theta);
  z = cos(phi);
}

Vector3D Vector3D::operator + (Vector3D rhs) {
  return Vector3D(x + rhs.getX(),
		  y + rhs.getY(),
		  z + rhs.getZ());
}
Vector3D Vector3D::operator - (Vector3D rhs) {
  return Vector3D(x - rhs.getX(),
		  y - rhs.getY(),
		  z - rhs.getZ());
}
Vector3D Vector3D::operator * (double rhs) {
  return Vector3D(x * rhs,
		  y * rhs,
		  z * rhs);
}
Vector3D Vector3D::operator / (double rhs) {
  return Vector3D(x / rhs,
		  y / rhs,
		  z / rhs);
}
double Vector3D::operator * (Vector3D rhs) {
  return dot(rhs);
}



double Vector3D::dot(Vector3D other) {
  return x*other.getX() + y*other.getY() + z*other.getZ();
}

Vector3D Vector3D::cross(Vector3D other) {
  return Vector3D(y*other.getZ() - z*other.getY(),
		  z*other.getX() - x*other.getZ(),
		  x*other.getY() - y*other.getX());
}

double Vector3D::length() {
  return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::unit() {
  return *this / length();
}

Vector3D Vector3D::rotate(double theta, double phi) {
  // theta and phi in radians
  // theta rotates about the z-axis, phi about the x-axis. Yaw and pitch.
  double thetaCurrent = getTheta();
  double phiCurrent = getPhi();
  return toCartesian(length(), thetaCurrent+theta, phiCurrent+phi);
}

Vector3D Vector3D::left90() {
  Vector3D ref(x, y, 0);
  if (z == 0) {
    ref = Vector3D(x, y, -0.0000001);
  };
  Vector3D vxUnit = cross(ref).unit();
  if (z < 0) {
    vxUnit = vxUnit * -1;
  }
  return vxUnit;
  
}
Vector3D Vector3D::right90() {
  return left90() * -1;
}
Vector3D Vector3D::up90() {
  Vector3D vyUnit = cross(left90()).unit();
  return vyUnit;
}
Vector3D Vector3D::down90() {
  return up90() * -1;
}

double Vector3D::getTheta() {
  return atan2(y,x);
}

double Vector3D::getPhi() {
  //cout << "PHI: " << atan2( sqrt(x*x + y*y), z ) << endl;
  return atan2( sqrt(x*x + y*y), z );
}


Vector3D Vector3D::refl(Vector3D norm) {
  return (*this - norm * (2 * (*this * norm))).unit();
}




Vector3D Vector3D::toCartesian(double rho, double theta, double phi) {
  //cout << "rho" << rho << " theta" << theta << " phi" << phi << endl;
  //cout << rho*sin(phi)*cos(theta) << endl;
  return Vector3D(rho*sin(phi)*cos(theta),
		  rho*sin(phi)*sin(theta),
		  rho*cos(phi));
}

void Vector3D::print() {
  std::cout << "{" << x << ", " << y << ", " << z << "},";
}
