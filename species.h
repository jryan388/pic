#ifndef SPECIES_H_INCLUDED__
#define SPECIES_H_INCLUDED__

#include "vector3d.h"
#include <string>
#include <iostream>

class Species {
 private:
  double mass;
  double charge;
  string name;

 public:
  Species(double mass_, double charge_, string name_);

  double getMass();

  double getCharge();

  string getName();
}
