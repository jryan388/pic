#ifndef SIM1D_H_INCLUDED__
#define SIM1D_H_INCLUDED__

#include <list>
#include <vector>
#include "vector3d.h"
#include <cmath>
#include "mymath.h"
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
  double dx;
  std::vector<double> grid;
  std::vector<std::vector<double>> poss;
  std::vector<std::vector<double>> vels;
  double m;
  double q;

  double e0 = 1;

  std::vector<double> den;
  std::vector<double> efield;
  
 public:
  Sim1D(int nCells_, double length_, Species spec_);

  void addParticle(double pos, double vel);

  void getDensity();

  void getEField();

  void advanceVelocity(double dt);

  void advancePosition(double dt);

  void step(double dt);

  void print();
  
  void printAll();
  
  void printRho();

  void printE();

  void printVelDist(double start, double end);
};

#endif
