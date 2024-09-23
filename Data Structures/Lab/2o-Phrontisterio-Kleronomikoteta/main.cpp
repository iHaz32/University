#include "Student.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  // The numbers will be printed with 1 decimal digit by default
  cout << fixed << setprecision(1);

  char surname[50];
  int id;
  double fee;

  cin >> surname;
  cin >> id;
  cin >> fee;

  Student *p = new Student();
  p->setSurname(surname);
  p->setId(id);
  p->setFee(fee);

  cout << p->getSurname() << ", " << p->getId() << ", " << p->getFee() << endl;

  delete p;

  cout << "Goodbye!" << endl;
  return 0;
}