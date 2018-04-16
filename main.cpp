#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include "vector3d.h"
#include "grid.h"

using namespace std;


int main(int argc, char *argv[]) {
  
  const int WIDTH = (argc == 3) ? atoi(argv[1]) : 320;
  const int HEIGHT = (argc == 3) ? atoi(argv[2]) : 240;
  const double FOVX = 60*(MyMath::PI/180); // needs to be in radians
  const double FOVY = FOVX * (double)HEIGHT / (double)WIDTH;
  const int MAX_RECURSION = 10;
  const double GAMMA = 2.2;
  const int numThreads = 4;
  const int linesPerThread = 5;

  Keyboard keyboard;
  /*Camera camera(Ray(Vector3D(-4.183, 13.5872, 4.97854), Vector3D(0.620364, -0.758735, -0.198669)), FOVX, FOVY, WIDTH, HEIGHT, true);
  Screen screen(HEIGHT, WIDTH, GAMMA, &camera, &keyboard);
  //Camera camera(Ray(Vector3D(0,0,0), Vector3D(1,0,0)), FOVX, FOVY, WIDTH, HEIGHT, true);
  Scene scene(Material(Color(1,1,1), 0, 0, 1, 50));
  // Material(Color(r,g,b), refl, transp, ior, illum)
  scene.add(new Sphere(Vector3D(7,0,0), 3, Material(Color(1,1,1), 0, .90, 1.2, 0)));
  //scene.add(new Sphere(Vector3D(-2,-5,5), 2, Material(Color(1,1,1), 0, 0, 1, 5000)));
  scene.add(new Sphere(Vector3D(6,-6,-1), 2, Material(Color(1,.2,.3), 0, 0, 1, 500)));
  scene.add(new Sphere(Vector3D(4,2,-2), 1, Material(Color(.1,.6,.1), 0, 0, 1, 500)));
  //scene.add(new Sphere(Vector3D(-50,0,0), 20, Material(Color(1,1,1), 0, 0, 1, 500)));
  scene.add(new Sphere(Vector3D(100010,0,0), 100000, Material(Color(1,.5,.5), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(8,4,3), 1, Material(Color(.2,.2,1), .97, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(8,4,-3), 1, Material(Color(1,.2,1), .97, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(5,-5,5), 4, Material(Color(1,1,1), .8, 0, 1, 0)));
  //scene.add(new Light(Vector3D(-10,3,3), 500, Color(1,1,1)));
  //scene.add(new Light(Vector3D(0,3,3), 5000, Color(1,0,0)));
  //scene.add(new Light(Vector3D(0,-3,3), 5000, Color(0,1,0)));
  //scene.add(new Light(Vector3D(0,0,-2), 5000, Color(0,0,1)));*/
  Camera camera(Ray(Vector3D(/*-18,0,0*/-18,3,3), Vector3D(/*1,0,0*/1,-.15,-.2).unit()), FOVX, FOVY, WIDTH, HEIGHT, true);
  Screen screen(HEIGHT, WIDTH, GAMMA, &camera, &keyboard);
  //Camera camera(Ray(Vector3D(0,0,0), Vector3D(1,0,0)), FOVX, FOVY, WIDTH, HEIGHT, true);
  Scene scene(Material(Color(1,1,1), 0, 0, 1, 200));
  //scene.add(new Sphere(Vector3D(0,0,0),5,Material(Color(1,1,1),0,1,1.0,0)));

  scene.add(new Sphere(Vector3D(100010,0,0),  100000, Material(Color(1.0,1.0,1.0), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(0,100010,0),  100000, Material(Color(0.2,1.0,0.2), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(0,-100010,0), 100000, Material(Color(1.0,0.2,0.2), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(0,0,100010),  100000, Material(Color(1.0,1.0,1.0), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(0,0,-100010), 100000, Material(Color(0.7,0.7,0.7), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(-100020,0,0), 100000, Material(Color(0.2,0.2,1.0), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(0,0,1),            4, Material(Color(1.0,1.0,1.0), .05, 1, 1.4, 0))); // glass ball
  scene.add(new Sphere(Vector3D(7,0,0),            3, Material(Color(1.0,1.0,1.0), 1, 0, 1, 0))); // mirror
  scene.add(new Sphere(Vector3D(6,-5.5,-7),        3, Material(Color(0.5,0.5,0.5), 0, 0, 1, 0)));
  scene.add(new Sphere(Vector3D(5,0,50),          42, Material(Color(1.0,1.0,1.0), 0, 0, 1, 1500))); // Light
  scene.add(new Sphere(Vector3D(8,-6.8,2),         3, Material(Color(0.0,1.0,0.3), 0, 0, 1, 2000))); // Light
  //scene.add(new Light(Vector3D(-10,3,3), 500, Color(1,1,1)));
  //scene.add(new Light(Vector3D(0,3,3), 5000, Color(1,0,0)));
  //scene.add(new Light(Vector3D(0,-3,3), 5000, Color(0,1,0)));
  //scene.add(new Light(Vector3D(0,0,-2), 5000, Color(0,0,1)));

  auto tcurr = chrono::high_resolution_clock::now();
  
  while (!keyboard.timeToQuit()) {
    auto tnew = chrono::high_resolution_clock::now();
    auto dt = tnew - tcurr;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(dt).count();
    cout << microseconds << endl;
    tcurr = tnew;
    
    camera.pixelRays();

    
    bool quit=false;

    int xStart = 0;
    while (xStart<WIDTH && !quit) {
      screen.processKeys();
      int dx = numThreads * linesPerThread;
      int xEnd = xStart + dx;
      if (xEnd > WIDTH) {
	xEnd = WIDTH;
      }
      bool found = false;
      #pragma omp parallel for
      for(int x = xStart; x < xEnd; x++) {
	vector< Color > col(HEIGHT);
	//#pragma omp parallel for
	for(int y=0; y<HEIGHT; y++) {
	//if (x==100 && y==100) {
	  Ray thisRay = camera.getRay(x, y);
	  Color color = scene.fire(thisRay, MAX_RECURSION);
	  col[y] = color;
	  //}
	}
	screen.addColumn(x, col);
      }
      for(int x = xStart; x < xEnd; x++) {
	screen.draw(x);
	quit = keyboard.timeToQuit() || screen.timeToRestart(x);
      }
      xStart = xEnd;
    }
      
      
      //screen.addFrame(frame);
      //screen.draw();
	
      //return 0;
    }
      
  

      scene.destroy();
      screen.quit();
  return 0;  
}
