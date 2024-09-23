#include "Product.h"
#include <iostream>
using namespace std;

ostream &operator<<(ostream &os, Product &A) {
  os << A.getName() << " " << A.getPrice();
  return os;
}