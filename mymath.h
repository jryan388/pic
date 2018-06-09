#ifndef MYMATH_H_INCLUDED__
#define MYMATH_H_INCLUDED__

#include <cstdlib>
#include <cmath>

namespace MyMath {
  inline double rand(){ 
    return (double)std::rand() / (double)RAND_MAX;
  };
  inline double rand(double end){ 
    return ((double)std::rand() / (double)RAND_MAX) * end;
  };
  inline double rand(double start, double end){ 
    return start + (((double)std::rand() / (double)RAND_MAX) * (end - start));
  };

  inline double positive(double val) {
    if (val < 0) {
      return 0;
    } else {
      return val;
    }
  }

  inline double clamp(double val) {
    if (val < 0) {
      return 0;
    } else if (val > 1) {
      return 1;
    } else {
      return val;
    }
  }

  inline double clamp(double val, double floor, double ceiling) {
    if (val < floor) {
      return floor;
    } else if (val > ceiling) {
      return ceiling;
    } else {
      return val;
    }
  }

  inline double binarize(double val) {
    if (val > 0.5) {
      return 1;
    } else {
      return 0;
    }
  }

  inline double binarize(double val, double floor, double ceiling) {
    if (val > ((ceiling + floor) / 2)) {
      return floor;
    } else {
      return ceiling;
    }
  }

  inline double binarize(double val, double floor, double ceiling, double threshold) {
    if (val > threshold) {
      return ceiling;
    } else {
      return floor;
    }
  }


  const double PI = 3.14159265358979323846;

  /*static inline double rand();
  static inline double rand(double end);
  static inline double rand(double start, double end);*/
};

#endif
