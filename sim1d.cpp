#include "sim1d.h"
#include <complex>
#include <fftw3.h>
#include <iomanip>

Sim1D::Sim1D(int nCells_, double length_, Species spec) {
  nCells = nCells_;
  length = length_;
  dx = length/((double)nCells);
  cellSize = length/((double)nCells);
  for (int i=0;i<nCells;i++) {
    grid.push_back((double)i*cellSize);
    den.push_back(0.0);
    efield.push_back(0.0);
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
  //std::cout << "Added particle " << xi << " " << pos << " " << dx << " " << vel << std::endl;
}

void Sim1D::getDensity() {
  for(int i=0; i<nCells; i++) {
    den[i] = 0;
  }
  for(int i=0; i<nCells; i++) {
    for(int j=0; j<poss[i].size(); j++) {
      double rx = poss[i][j]/cellSize;
      den[i] += q*(1.0-rx);
      int i2 = (i+1 == nCells ? 0 : i+1);
      //std::cout << "i2 " << i2 << " rx " << rx << std::endl;
      den[i2] += q*rx;
    }
  }
}

void Sim1D::getEField() {
  double* in;
  fftw_complex* out;
  fftw_plan p;
  in = (double*) fftw_malloc(sizeof(double) * nCells);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nCells);
  for(int i=0; i<nCells; i++) {
    in[i] = den[i];
  }

  p = fftw_plan_dft_r2c_1d(nCells, in, out, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  
  //std::cout << "arr" << std::endl;
  // Take the abbreviated array and fill it out; the second half of the array is the conjugate of the first half.
  for (int i=std::ceil(nCells/2)+1; i<nCells; i++) {
    out[i][0] = out[nCells-i][0];
    out[i][1] = out[nCells-i][1] * -1.0;
  }
  //for (int i=0; i<nCells/*std::ceil(nCells/2)+1*/; i++) {
  //  std::cout << out[i][0] << " " << out[i][1] << std::endl;
  //}

  // Now turn the output rho(k) into phi(k). phi(k) = rho(k)/(e0*bigK^2). Also, bigK^2=k^2*dif(g)^2 and g=k*dx/2
  double dxe0 = dx/e0; // Factor dx in front is half of the normalization of the FFT
  double k0 = 2*MyMath::PI/length;
  out[0][0] = 0; // phi[k] does not have a DC term in our gauge of choice.
  for (int i=1; i<nCells; i++) {
    double kdx2 = i*k0*dx/2.0;
    double difkdx2 = std::sin(kdx2)/kdx2;
    double bigK2 = i*k0*i*k0*difkdx2*difkdx2;
    double fac = dxe0 / bigK2;
    out[i][0] *= fac;
    out[i][1] *= fac;
  }

  // Now turn output phi(k) into E(k). E(k) = -i*kappa*phi(k) with kappa=k*sin(k*dx)/(k*dx)
  for (int i=1; i<nCells; i++) {
    double kappa = std::sin(i*k0*dx)/dx;
    double temp = out[i][1]*kappa;
    out[i][1] = -1.0*kappa*out[i][0];
    out[i][0] = temp;
  }

  // Finally inverse FFT to get E(x).
  p = fftw_plan_dft_c2r_1d(nCells, out, in, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  //std::cout << "E FIELD: " << std::endl;
  for (int i=0; i<nCells/*std::ceil(nCells/2)+1*/; i++) {
    //std::cout << in[i] << std::endl;
    efield[i] = in[i];
  }
  //std::cout << "That was the E field. " << std::endl;
  
  fftw_free(in);
  fftw_free(out);
}

void Sim1D::advanceVelocity(double dt) {
  for (int i=0; i<nCells; i++) {
    int i2 = i+1 == nCells ? 0 : i+1;
    double Ea = efield[i];
    double Eb = efield[i2];
    for (int j=0; j<poss[i].size(); j++) {
      double rx = poss[i][j]/cellSize;
      double Ehere = Ea*(1.0-rx) + Eb*rx;
      vels[i][j] += q/m*Ehere*dt;
    }
  }
}

void Sim1D::advancePosition(double dt) {
  std::vector< std::vector<double> > poss2;
  std::vector< std::vector<double> > vels2;
  for (int i=0;i<nCells;i++) {
    std::vector<double> posi;
    std::vector<double> veli;
    poss2.push_back(posi);
    vels2.push_back(veli);
  }

  for (int i=0; i<nCells; i++) {
    auto possi = poss[i];
    auto velsi = vels[i];
    for(int j=0; j<poss[i].size(); j++) {
      //auto posIter=poss[i].begin(), velIter=vels[i].begin(); posIter!=poss[i].end() && velIter!=vels[i].end(); ++posIter, ++velIter) {
      //double vel = *velIter;
      //double pos = *posIter + vel*dt;
      double vel = velsi[j];
      double pos = possi[j] + dt*vel;
      int i2 = i;
      if (pos > cellSize) {
	pos -= cellSize;
	i2 = i+1 == nCells ? 0 : i+1;
      } else if (pos < 0) {
	pos += cellSize;
	i2 = i-1 == -1 ? nCells-1 : i-1;
      }
      poss2[i2].push_back(pos);
      vels2[i2].push_back(vel);
    }
  }

  vels = vels2;
  poss = poss2;
}

void Sim1D::step(double dt) {
  getDensity();
  getEField();
  advanceVelocity(dt/2.0);
  advancePosition(dt);
  advanceVelocity(dt/2.0);

  

  /*for (int i=0; i<nCells; i++) {
    for (int j=0; j<poss[i].size(); j++) {
      std::cout << "Cell " << i << " position " << poss[i][j] << std::endl;
    }
    }*/
  
  //for (int i=0;i<nCells;i++) {
  //  std::cout << den[i] << std::endl;
  //}
  
}


void Sim1D::print() {
  for (int i=0; i<nCells; i++) {
    if (poss[i].size() == 0) {
      std::cout << '.';
    } else {
      std::cout << poss[i].size();
    }
  }
  std::cout << std::endl;
}
void Sim1D::printAll() {
  for (int i=0; i<nCells; i++) {
    std::cout << "Cell " << i << " position " << grid[i] << std::endl;
    for (int j=0; j<poss[i].size(); j++) {
      std::cout << poss[i][j] << std::endl;
    }
  }
  std::cout << "That's all the cell contents." << std::endl;
}

void Sim1D::printRho() {
  for (int i=0; i<nCells; i++) {
    std::cout << den[i] << std::endl;
  }
  std::cout << std::endl;
}

void Sim1D::printE() {
  for (int i=0; i<nCells; i++) {
    std::cout << efield[i] << std::endl;
  }
  std::cout << std::endl;
}

void Sim1D::printVelDist(double start, double end) {
  int numBins = 20;
  std::vector<int> bins;
  std::vector<double> locs;
  for(int i=0; i<numBins; i++) {
    bins.push_back(0);
    locs.push_back(start + (end-start)/numBins*i);
  }
  for(int i=0;i<vels.size();i++) {
    for(int j=0;j<vels[i].size();j++) {
      int idx = std::floor((vels[i][j]-start)/(end-start)*numBins);
      if (idx >= numBins or idx < 0) {
	idx = numBins-1;
	//std::cout<<"Value outside histogram: " << vels[i][j] << std::endl;
      }
      bins[idx]++;
    }
  }
  std::cout<<"Distribution:"<<std::endl;
  for(int i=0; i<bins.size(); i++) {
    std::cout << std::setw(6) << locs[i] << " ";
    for (int j=0; j<bins[i]; j=j+100) {
      std::cout << ".";
    }
    std::cout << std::endl;
  }
}
