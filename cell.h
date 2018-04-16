#ifndef CELL_H_INCLUDED__
#define CELL_H_INCLUDED__

#include <vector>
#include "vector3d.h"
#include <string>
#include <iostream>

class Cell {
 private:
  double originX;
  double originY;
  vector< vector< Vector3D > > poss;
  vector< vector< Vector3D > > vels;
  
 public:
  Cell(double originX_, double originY_, vector< vector< poss_ > >, vector< vector< vels_ > >);
    
  
}
