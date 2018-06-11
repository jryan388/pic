#ifndef SIM1D_H_INCLUDED__
#define SIM1D_H_INCLUDED__

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

class Sim1D {
  int nCells;
  double length;
  double cellSize;
  std::vector<double> grid;
  std::vector<std::vector<double>> poss;
  std::vector<std::vector<double>> vels;
  double m;
  double q;

  std::vector<double> den;
  std::vector<double> pot;
  
 public:
  Sim1D(int nCells_, double length_, Species spec_);

  void addParticle(double pos, double vel);

  void getDensity();

  void step(double dt);
  
};

#endif
