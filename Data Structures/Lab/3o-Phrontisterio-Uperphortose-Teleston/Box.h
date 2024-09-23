#ifndef BOX_H
#define BOX_H

#include <iostream>
using namespace std;

class Box {
protected:
  double x;
  double y;
  double z;

public:
  Box();
  Box(double x, double y, double z);

  void setX(double x);
  double getX();
  void setY(double y);
  double getY();
  void setZ(double z);
  double getZ();

  bool operator==(Box B);
  bool operator!=(Box B);
  Box operator=(Box B);
  Box operator++();
  Box operator++(int dummy);
  Box operator--();
  Box operator--(int dummy);
  Box operator+=(double l);
  Box operator-=(double l);
  Box operator*=(double l);
  Box operator/=(double l);
  friend ostream &operator<<(ostream &mystream, const Box &p);
};
Box operator*(Box A, double l);
Box operator/(Box A, double l);
Box operator+(Box A, double l);
Box operator-(Box A, double l);
Box operator+(Box A, Box B);
Box operator-(Box A, Box B);

#endif