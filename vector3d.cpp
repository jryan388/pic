#include "vector3d.h"
#include <cmath>
#include <string>
#include <iostream>

Vector3D Vector3D::operator + (Vector3D rhs) {
  return Vector3D(x + rhs.x,
		  y + rhs.y,
		  z + rhs.z);
}
Vector3D Vector3D::operator - (Vector3D rhs) {
  return Vector3D(x - rhs.x,
		  y - rhs.y,
		  z - rhs.z);
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

void Vector3D::print() {
  std::cout << "{" << x << ", " << y << ", " << z << "},";
}
