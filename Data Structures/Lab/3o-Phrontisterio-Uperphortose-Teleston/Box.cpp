#include "Box.h"
#include <iostream>
using namespace std;

Box::Box() {
  x = 0;
  y = 0;
  z = 0;
}

Box::Box(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

void Box::setX(double x) { this->x = x; }

double Box::getX() { return x; }

void Box::setY(double y) { this->y = y; }

double Box::getY() { return y; }

void Box::setZ(double z) { this->z = z; }

double Box::getZ() { return z; }

Box operator*(Box A, double l) {
  Box B;
  B.setX(A.getX() * l);
  B.setY(A.getY() * l);
  B.setZ(A.getZ() * l);
  return B;
}

Box operator/(Box A, double l) {
  Box B;
  B.setX(A.getX() / l);
  B.setY(A.getY() / l);
  B.setZ(A.getZ() / l);
  return B;
}

Box operator+(Box A, double l) {
  Box B;
  B.setX(A.getX() + l);
  B.setY(A.getY() + l);
  B.setZ(A.getZ() + l);
  return B;
}

Box operator+(Box A, Box B) {
  Box C;
  C.setX(A.getX() + B.getX());
  C.setY(A.getY() + B.getY());
  C.setZ(A.getZ() + B.getZ());
  return C;
}

Box operator-(Box A, double l) {
  Box B;
  B.setX(A.getX() - l);
  B.setY(A.getY() - l);
  B.setZ(A.getZ() - l);
  return B;
}

Box operator-(Box A, Box B) {
  Box C;
  C.setX(A.getX() - B.getX());
  C.setY(A.getY() - B.getY());
  C.setZ(A.getZ() - B.getZ());
  return C;
}

bool Box::operator==(Box B) {
  if (this->getX() == B.getX() && this->getY() == B.getY() &&
      this->getZ() == B.getZ()) {
    return true;
  }
  return false;
}

bool Box::operator!=(Box B) {
  if (this->getX() != B.getX() || this->getY() != B.getY() ||
      this->getZ() != B.getZ()) {
    return true;
  }
  return false;
}

Box Box::operator=(Box A) {
  this->x = A.getX();
  this->y = A.getY();
  this->z = A.getZ();
  return A;
}

Box Box::operator++() {
  this->setX(this->getX() + 1);
  this->setY(this->getY() + 1);
  this->setZ(this->getZ() + 1);
  return *this;
}

Box Box::operator++(int dummy) {
  Box r = *this;
  x = x + 1;
  y = y + 1;
  z = z + 1;
  return r;
}

Box Box::operator--() {
  this->setX(this->getX() - 1);
  this->setY(this->getY() - 1);
  this->setZ(this->getZ() - 1);
  return *this;
}

Box Box::operator--(int dummy) {
  Box r = *this;
  x = x - 1;
  y = y - 1;
  z = z - 1;
  return r;
}

Box Box::operator+=(double l) {
  x += l;
  y += l;
  z += l;
  return *this;
}
Box Box::operator-=(double l) {
  x -= l;
  y -= l;
  z -= l;
  return *this;
}

Box Box::operator*=(double l) {
  x *= l;
  y *= l;
  z *= l;
  return *this;
}

Box Box::operator/=(double l) {
  x /= l;
  y /= l;
  z /= l;
  return *this;
}

ostream &operator<<(ostream &os, const Box &A) {
  os << "length: " << A.x << ", width: " << A.y << ", height: " << A.z;
  return os;
}
