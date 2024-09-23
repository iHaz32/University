#include "Student.h"
#include <cmath>
#include <iostream>
#include <math.h>

using namespace std;

Student::Student() { fee = 0; }

Student::~Student() { cout << "destructor in Student" << endl; }

void Student::setFee(double fee) { this->fee = fee; }

double Student::getFee() { return fee; }