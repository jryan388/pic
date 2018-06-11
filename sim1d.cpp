#include "sim1d.h"

Sim1D::Sim1D(int nCells_, double length_, Species spec) {
  nCells = nCells_;
  length = length_;
  cellSize = length/((double)nCells);
  for (int i=0;i<nCells;i++) {
    grid.push_back((double)i*cellSize);
    den.push_back(0.0);
    pot.push_back(0.0);

    std::vector<double> posi;
    std::vector<double> veli;
    poss.push_back(posi);
    vels.push_back(veli);
  }
  m = spec.mass;
  q = spec.charge;
}

void Sim1D::addParticle(double pos, double vel) {
  int xi = std::floor(pos/cellSize);
  double dx = pos - ((double)xi)*cellSize;
  poss[xi].push_back(dx);
  vels[xi].push_back(vel);
  std::cout << "Added particle " << xi << " " << pos << " " << dx << " " << vel << std::endl;
}

void Sim1D::getDensity() {
  for(int i=0; i<nCells; i++) {
    den[i] = 0;
  }
  for(int i=0; i<nCells; i++) {
    for(int j=0; j<poss[i].size(); j++) {
      double rx = poss[i][j]/cellSize;
      den[i] += q*rx;
      int i2 = (i+1 == nCells ? 0 : i+1);
      //std::cout << "i2 " << i2 << " rx " << rx << std::endl;
      den[i2] += q*(1.0-rx);
    }
  }
}

void Sim1D::step(double dt) {
  getDensity();
  for (int i=0;i<nCells;i++) {
    std::cout << den[i] << std::endl;
  }
  
}
