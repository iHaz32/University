#include "ElectricalScooter.h"

ElectricalScooter::ElectricalScooter() {
  maxKM = 0;
  year = 0;
  timeM = 0;
}

ElectricalScooter::ElectricalScooter(int maxKM, int year, int timeM) {
  this->maxKM = maxKM;
  this->year = year;
  this->timeM = timeM;
}

double ElectricalScooter::getPollutionScore() { return timeM * 300.0 / 365; }

double ElectricalScooter::getTaxes() { return (2022 - year) * 12.5 * 80 / 100; }

int ElectricalScooter::getChargingTime() { return timeM; }

void ElectricalScooter::setChargingTime(int timeM) { this->timeM = timeM; }