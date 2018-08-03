#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include "mymath.h"
#include "vector3d.h"
#include "grid.h"
#include "species.h"
#include "sim.h"
#include "sim1d.h"
#include <ctime>
#include <cmath>

int main(int argc, char *argv[]) {

  std::srand(std::time(NULL));
  
  const int WIDTH = (argc == 3) ? atoi(argv[1]) : 320;
  const int HEIGHT = (argc == 3) ? atoi(argv[2]) : 240;
  const double FOVX = 60*(MyMath::PI/180); // needs to be in radians
  const double FOVY = FOVX * (double)HEIGHT / (double)WIDTH;
  const int MAX_RECURSION = 10;
  const double GAMMA = 2.2;
  const int numThreads = 4;
  const int linesPerThread = 5;

  bool quit=false;

  Species electron(1,-1,"electron");
  
  std::cout << "Starting program" << std::endl;
  //  Grid grid(10,1,1,Vector3D(1.0,1.0,1.0));
  //grid.addParticle(Vector3D(1.6,0.6,0.7),
  //		   Vector3D(1.5,1.6,1.7),
  //		   electron);
  //Vector3D vec1 = Vector3D(1.2,2.2,3.2);

  int particleCount = 10;
  double length = 10.0;
  int cells = 256;
  
  Sim1D* sim = new Sim1D(cells, length, electron);

  //std::vector<double> vels = MyMath::maxwellDist(10,1,0,10);
  //for (int i=0; i<vels.size(); i++) {
  //  std::cout << vels[i] << std::endl;
  //}

  int numPts = 10000;
  int distCells = 500;
  double start = -5;
  double end = 35;
  double a = 0.5;
  double x1 = 5;
  double x2 = 25;
  std::vector<double> dist1 = MyMath::gaussianDistOrdered(numPts, distCells, a, x1, start, end);
  std::vector<double> dist2 = MyMath::gaussianDistOrdered(numPts, distCells, a, x2, start, end);

  for(int i=0;i<dist1.size();i++) {
    sim->addParticle(length*MyMath::rand(),dist1[i]);
  }
  for(int i=0;i<dist2.size();i++) {
    sim->addParticle(length*MyMath::rand(),dist2[i]);
  }
  
  //sim->addParticle(length/cells*0.5, 0);
  //sim->addParticle(length/cells*0.6, 0);
    
  double tEnd = 100;
  double dt = 0.0001;
  
  int n=0;

  for (double t=0; t<tEnd; t+=dt) {
    sim->step(dt);
    if (n % 100 == 0) {
      sim->printVelDist(start, end);
      //sim->print();
      //std::cout << "Rho:" << std::endl;
      //sim->printRho();
      //std::cout << "E:" << std::endl;
      //sim->printE();
    }
    n++;
  }
  //sim->printE();

  sim->printVelDist(start, end);
  
  return 0;  
}
