#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student : public Person {
private:
  double fee;

public:
  Student();
  ~Student();
  void setFee(double);
  double getFee();
};

#endif