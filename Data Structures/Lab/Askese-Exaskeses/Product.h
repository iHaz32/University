#ifndef PRODUCT_H
#define PRODUCT_H

#include "Date.h"

class Product {
protected:
  char name[20];
  Date expiry;
  int grams;

public:
  Product();
  Product(char *, Date, int);
  char *Getname();
  Date getExpiry();
};

#endif