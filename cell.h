#ifndef CELL_H_INCLUDED__
#define CELL_H_INCLUDED__

#include <list>
#include <vector>
#include "vector3d.h"
#include <string>
#include <iostream>
#include "species.h"
#include "cube.h"

class Cell {
 private:
  Vector3D origin;
  Vector3D size;
  std::vector< std::vector< Vector3D >* > poss;
  std::vector< std::vector< Vector3D >* > vels;
  std::vector< Species > species;
  
 public:
  Cell(Vector3D origin, Vector3D size);
    
  void addParticle(Vector3D pos, Vector3D vel, Species speciesNew);

  void print();

  Cube getDensity();
};

#endif
