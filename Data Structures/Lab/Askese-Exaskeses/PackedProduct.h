#ifndef PACKEDPRODUCT_H
#define PACKEDPRODUCT_H

#include "Product.h"
#include <iostream>
#include <string.h>

class PackedProduct : public Product {
private:
  bool open;
  int lifetime;
  Date opened;

public:
  PackedProduct();
  PackedProduct(char *name, Date expiry, int grams, bool open, int lifetime,
                Date opened) {
    strcpy(this->name, name);
    this->expiry.setDate(expiry.getDate());
    this->expiry.setMonth(expiry.getMonth());
    this->expiry.setYear(expiry.getYear());
    this->grams = grams;
    this->open = open;
    this->lifetime = lifetime;
    this->opened.setDate(opened.getDate());
    this->opened.setMonth(opened.getMonth());
    this->opened.setYear(opened.getYear());
    if (open) {
      this->expiry.setDate(opened.getDate());
      this->expiry.setMonth(opened.getMonth());
      this->expiry.setYear(opened.getYear());
      this->expiry.add(lifetime);
    }
  }
};

#endif