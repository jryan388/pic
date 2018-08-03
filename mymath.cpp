#include "mymath.h"


namespace MyMath {

  std::vector<double> gaussianDistOrdered(int len, int cells, double a, double x0, double start, double end) {
    int n = 0;
    std::vector<double> dist;

    double totProb = 0;
    double dx = (end-start)/cells; // Width of a cell in units of x
    for(int i=0; i<cells; i++) {
      double pos = dx*(i+0.5);
      totProb += std::exp(-(pos-x0)*(pos-x0)/(2*a*a));
      //std::cout << "Cell " << i << " totProb " << totProb << std::endl;
    }
    double dProb = totProb/(len+0.9999); // Probability per point
    double probWaiting = 0;
    for(int i=0; i<cells; i++) {
      double center = dx*(i+0.5);
      probWaiting += std::exp(-(center-x0)*(center-x0)/(2*a*a));
      int pointsHere = std::floor(probWaiting / dProb);
      //std::cout << "Cell " << i << " x " << center << " pointsHere " << pointsHere << " probW "<< probWaiting << std::endl;
      probWaiting -= pointsHere*dProb;
      if (pointsHere>0) {
	double ddx = dx/pointsHere;
	//std::cout << " ddx: " << ddx << std::endl;
	for (int j=0; j<pointsHere; j++) {
	  dist.push_back(i*dx + (j+0.5)*ddx);
	  std::cout <<i*dx + (j+0.5)*ddx << std::endl;
	  //std::cout <<i<<" "<<dx<<" "<<j/(pointsHere+1.0)<<" "<<ddx<<std::endl;
	}
      }
    }
    return dist;
  }  

  std::vector<double> gaussianDistMC(int len, double a, double x0, double start, double end) {
    int n = 0;
    std::vector<double> dist;
    while (n<len) {
      double x = rand(start, end);
      if (rand() < std::exp(-(x-x0)*(x-x0)/(2*a*a))) {
	dist.push_back(x);
	n++;
      }
    }
    return dist;
  }

  double maxwellPDF3D(double x, double a) {
    return std::sqrt(2/PI)*x*x/(a*a*a)*std::exp(-x*x/(2*a*a));
  }


  std::vector<double> maxwellDist3D(int len, double a, double start, double end) {
    double xPeak = 2*std::sqrt(2/PI)/a/std::exp(1);
    //std::cout << "xPeak: " << xPeak << std::endl;
    double probPeak = maxwellPDF3D(xPeak, a);
    //std::cout << "probPeak: " << probPeak << std::endl;

    int n = 0;
    std::vector<double> dist;
    while (n<len) {
      double x = rand(start, end);
      if (rand(probPeak) < maxwellPDF3D(x,a)) {
	dist.push_back(x);
	n++;
      }
    }
    return dist;
  }

}
