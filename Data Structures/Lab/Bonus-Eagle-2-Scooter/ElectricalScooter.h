#ifndef ELECTRICALSCOOTER_H
#define ELECTRICALSCOOTER_H

#include "Scooter.h"
class ElectricalScooter : public Scooter {
private:
  int timeM;

public:
  ElectricalScooter();
  ElectricalScooter(int, int, int);
  double getPollutionScore();
  double getTaxes();
  int getChargingTime();
  void setChargingTime(int);
};

#endif