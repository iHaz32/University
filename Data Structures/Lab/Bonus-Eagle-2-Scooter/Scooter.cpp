#include "Scooter.h"

Scooter::Scooter() {
  maxKM = 0;
  year = 0;
}

Scooter::Scooter(int maxKM, int year) {
  this->maxKM = maxKM;
  this->year = year;
}

int Scooter::getMaxKM() { return maxKM; }

int Scooter::getYear() { return year; }

double Scooter::getPollutionScore() { return maxKM * 250.0 / 365; }

double Scooter::getTaxes() { return (2022 - year) * 12.5; }