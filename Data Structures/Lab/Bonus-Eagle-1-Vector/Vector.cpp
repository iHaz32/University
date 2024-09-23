#include "Vector.h"
#include <cmath>
#include <iostream>
#include <math.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif

Vector::Vector() {
  x = 0;
  y = 0;
}

Vector::Vector(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector::SetX(double x) { this->x = x; }

void Vector::SetY(double y) { this->y = y; }

double Vector::GetX() { return x; }

double Vector::GetY() { return y; }

double Vector::magnitude() { return sqrt(pow(x, 2) + pow(y, 2)); }

double Vector::angle() { return atan(y / x); }

double Vector::angleD() { return atan(y / x) * 180 / M_PI; }

void Vector::multiply(double f) {
  x = f * x;
  y = f * y;
}

Vector Vector::add(Vector vector) {
  Vector newVector;
  newVector.x = x + vector.x;
  newVector.y = y + vector.y;
  return newVector;
}

Vector Vector::clone() {
  Vector newVector;
  newVector.x = x;
  newVector.y = y;
  return newVector;
}