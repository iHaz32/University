#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
  double x;
  double y;

public:
  Vector();
  Vector(double, double);
  void SetX(double);
  void SetY(double);
  double GetX();
  double GetY();
  double magnitude();
  double angle();
  double angleD();
  void multiply(double);
  Vector add(Vector);
  Vector clone();
};

#endif