#include "Product.h"
#include <cstring>
#include <iostream>
using namespace std;

Product::Product(unsigned int id, char *name, float price) {
  this->id = id; // copy id

  this->name = new char[strlen(name) + 1]; // allocate memory
  strcpy(this->name, name);                // copy name

  this->price = price; // copy price
}

Product::~Product() { delete[] name; }

unsigned int Product::getId() { return id; }

char *Product::getName() { return name; }

float Product::getPrice() { return price; }