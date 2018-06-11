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
  int cells = 5;
  
  Sim1D* sim = new Sim1D(cells, length, electron);

  for (int i=0;i<particleCount;i++) {
    sim->addParticle(length*MyMath::rand(), MyMath::rand());
  }

  double tEnd=1;
  double dt=0.1;
  for (double t=0; t<tEnd; t+=dt) {
    sim->step(dt);
  }
  
  return 0;  
}
