#include "cell.h"

Cell::Cell(Vector3D origin_, Vector3D size_) {
  origin = origin_;
  size = size_;
}


void Cell::addParticle(Vector3D pos, Vector3D vel, Species speciesNew) {
  bool found = false;
  for(std::size_t i=0; i<species.size(); ++i) {
    if (species[i].name == speciesNew.name) {
      found = true;
      poss[i]->push_back(pos);
      vels[i]->push_back(vel);
    }
  }
  if (found == false) {
    std::cout << "Can't find the species." << std::endl;
    species.push_back(speciesNew);

    std::vector< Vector3D >* posList = new std::vector< Vector3D >;
    posList->push_back(pos);
    poss.push_back(posList);

    std::vector< Vector3D >* velList = new std::vector< Vector3D >;
    velList->push_back(vel);
    vels.push_back(velList);
  }
  std::cout << "Added new particle." << std::endl;
  print();
}



void Cell::print() {
  std::cout << "Contents of cell with origin (" << origin.x << ", "
	    << origin.y << ", " << origin.z << ") " << std::endl;
  for (std::size_t i=0; i<species.size(); ++i) {
    std::cout << "--Species " << species[i].name << " with mass " << species[i].mass
	      << " and charge " << species[i].charge << std::endl;
    for (std::size_t j=0; j<poss[i]->size(); ++j) {
      std::vector< Vector3D >& possi = *(poss[i]);
      std::vector< Vector3D >& velsi = *(vels[i]);
      std::cout << "----Particle with position ("
		<< possi[j].x << ", " << possi[j].y << ", " << possi[j].z
		<< ") and velocity ("
		<< velsi[j].x << ", " << velsi[j].y << ", " << velsi[j].z
		<< ")" << std::endl;
    }
  }
}
