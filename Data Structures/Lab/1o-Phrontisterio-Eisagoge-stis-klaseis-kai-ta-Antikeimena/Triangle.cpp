#include "Triangle.h"
#include <cmath>
#include <math.h>

#ifndef E
#define E 0.0001
#endif

#ifndef M_PI
#define M_PI 3.14159265
#endif // M_PI

Triangle::Triangle() {
  XA = 0;
  YA = 0;
  XB = 0;
  YB = 0;
  XC = 0;
  YC = 0;
}
Triangle::Triangle(double xa, double ya, double xb, double yb, double xc,
                   double yc) {
  XA = xa;
  YA = ya;
  XB = xb;
  YB = yb;
  XC = xc;
  YC = yc;
}
void Triangle::SetXA(double input) { XA = input; }
void Triangle::SetYA(double input) { YA = input; }
void Triangle::SetXB(double input) { XB = input; }
void Triangle::SetYB(double input) { YB = input; }
void Triangle::SetXC(double input) { XC = input; }
void Triangle::SetYC(double input) { YC = input; }
double Triangle::GetXA() { return XA; }
double Triangle::GetYA() { return YA; }
double Triangle::GetXB() { return XB; }
double Triangle::GetYB() { return YB; }
double Triangle::GetXC() { return XC; }
double Triangle::GetYC() { return YC; }

double Triangle::getAB() { return sqrt(pow((XA - XB), 2) + pow((YA - YB), 2)); }
double Triangle::getBC() { return sqrt(pow((XB - XC), 2) + pow((YB - YC), 2)); }
double Triangle::getAC() { return sqrt(pow((XA - XC), 2) + pow((YA - YC), 2)); }
double Triangle::getA() {
  return acos((pow(getAC(), 2) + pow(getAB(), 2) - pow(getBC(), 2)) /
              (2 * getAC() * getAB()));
}
double Triangle::getB() {
  return acos((pow(getAB(), 2) + pow(getBC(), 2) - pow(getAC(), 2)) /
              (2 * getAB() * getBC()));
}
double Triangle::getC() {
  return acos((pow(getAC(), 2) + pow(getBC(), 2) - pow(getAB(), 2)) /
              (2 * getAC() * getBC()));
}

bool Triangle::isIsopleurous() {
  return fabs(getAB() - getAC()) < E && fabs(getAB() - getBC()) < E;
}
bool Triangle::isIsosceles() {
  return (fabs(getBC() - getAC()) < E || fabs(getBC() - getAB()) < E ||
          fabs(getAB() - getAC()) < E);
}
bool Triangle::isScalino() {
  return fabs(getAB() - getAC()) >= E && fabs(getAB() - getBC()) >= E &&
         fabs(getBC() - getAC()) >= E;
}
bool Triangle::isOrthogonio() {
  return (fabs(getA() * 180 / M_PI - 90) < E ||
          fabs(getB() * 180 / M_PI - 90) < E ||
          fabs(getC() * 180 / M_PI - 90) < E);
}
bool Triangle::isOxygonio() {
  return (getA() * 180 / M_PI < 90 && getB() * 180 / M_PI < 90 &&
          getC() * 180 / M_PI < 90);
}
bool Triangle::isAmvligonio() {
  return (getA() * 180 / M_PI > 90 || getB() * 180 / M_PI > 90 ||
          getC() * 180 / M_PI > 90);
}

double Triangle::getBase() { return getAB(); }
double Triangle::getHeight() {
  return sin(getA())*getAC();
}
double Triangle::getArea() { return getBase() * getHeight() / 2; }