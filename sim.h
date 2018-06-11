#ifndef SIM_H_INCLUDED__
#define SIM_H_INCLUDED__

#include <list>
#include <vector>
#include "vector3d.h"
#include <cmath>
#include <string>
#include <iostream>
#include "cell.h"
#include "species.h"
#include "cube.h"
#include "grid.h"

class Sim {
  std::string intMethod;
  
  Grid* grid;
  
 public:
  Sim(std::string intMethod_);

  void init(int nx, int ny, int nz, Vector3D size);
  
  void addParticle(Vector3D pos, Vector3D vel, Species spec);
    
};

#endif
