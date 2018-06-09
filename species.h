#ifndef SPECIES_H_INCLUDED__
#define SPECIES_H_INCLUDED__

#include "vector3d.h"
#include <string>
#include <iostream>

struct Species {
  double mass;
  double charge;
  std::string name;
  
Species(double mass_, double charge_, std::string name_) : mass(mass_), charge(charge_), name(name_) {}
};

#endif
