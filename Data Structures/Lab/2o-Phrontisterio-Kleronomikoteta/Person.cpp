#include "Person.h"
#include <cstring>
#include <iostream>
#include <string.h>

using namespace std;

Person::Person() {
  id = 0;
  strcpy(surname, " ");
}

Person::Person(int id, char *name) {
  this->id = id;
  strcpy(surname, name);
}

Person::~Person() { cout << "destructor in Person" << endl; }

void Person::setId(int id) { this->id = id; }

void Person::setSurname(char *name) { strcpy(surname, name); }

int Person::getId() { return id; }

char *Person::getSurname() { return surname; }