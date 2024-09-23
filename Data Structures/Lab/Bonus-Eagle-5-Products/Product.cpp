#include "Product.h"
#include <cstring>
#include <iostream>
using namespace std;

Product::Product() {
  name = new char[1]; //"\0";
  strcpy(name, "");
  price = 0;
}

Product::Product(const char *name, float price) {
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
  this->price = price;
}

char *Product::getName() { return name; }

void Product::setName(const char *name) {
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}

float Product::getPrice() { return price; }

void Product::setPrice(float price) { this->price = price; }

Product::~Product() { delete[] name; }