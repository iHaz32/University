#include "Product.h"
#include <cstring>
#include <string.h>

Product::Product() {}

Product::Product(char *name, Date expiry, int grams) {
  strcpy(this->name, name);
  this->expiry.setDate(expiry.getDate());
  this->expiry.setMonth(expiry.getMonth());
  this->expiry.setYear(expiry.getYear());
}

char *Product::Getname() { return name; }

Date Product::getExpiry() { return expiry; }