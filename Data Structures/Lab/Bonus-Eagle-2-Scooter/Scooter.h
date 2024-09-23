#ifndef SCOOTER_H
#define SCOOTER_H

class Scooter {
protected:
  int maxKM;
  int year;

public:
  Scooter();
  Scooter(int, int);
  int getMaxKM();
  int getYear();
  virtual double getPollutionScore();
  virtual double getTaxes();
};

#endif