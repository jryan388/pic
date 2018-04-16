#ifndef SPECIES_H_INCLUDED__
#define SPECIES_H_INCLUDED__

#include "vector3d.h"
#include <string>
#include <iostream>

Species::Species(double mass_, double charge_, string name_){
  mass = mass_;
  charge = charge_;
  name = name_;
}

double Species::getMass() { return mass; }

double Species::getCharge() { return charge; }

string Species::getName() { return name; }
