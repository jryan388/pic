#ifndef GRID_H_INCLUDED__
#define GRID_H_INCLUDED__

#include <list>
#include <vector>
#include "vector3d.h"
#include <cmath>
#include <string>
#include <iostream>
#include "cell.h"
#include "species.h"
#include "cube.h"

class Grid {
 private:
  std::vector< std::vector< std::vector< Cell* > > > cells;
  Vector3D cellSize;
  int cellsX;
  int cellsY;
  int cellsZ;
  

  
 public:
  Grid(int cellsX_, int cellsY_, int cellsZ_, Vector3D cellSize_);

  void addParticle(Vector3D pos_, Vector3D vel_, Species species_);

  Cell* getCell(int ix, int iy, int iz);

  void computeDensity();
  
};

#endif
