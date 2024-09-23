#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
private:
  double XA;
  double YA;
  double XB;
  double YB;
  double XC;
  double YC;

public:
  Triangle();
  Triangle(double xa, double ya, double xb, double yb, double xc, double yc);
  void SetXA(double input);
  void SetYA(double input);
  void SetXB(double input);
  void SetYB(double input);
  void SetXC(double input);
  void SetYC(double input);
  double GetXA();
  double GetYA();
  double GetXB();
  double GetYB();
  double GetXC();
  double GetYC();

  double getAB();
  double getBC();
  double getAC();
  double getA();
  double getB();
  double getC();

  bool isIsopleurous();
  bool isIsosceles();
  bool isScalino();
  bool isOrthogonio();
  bool isOxygonio();
  bool isAmvligonio();

  double getBase();
  double getHeight();
  double getArea();
};

#endif