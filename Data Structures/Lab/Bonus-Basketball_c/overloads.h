#include "BasketballPlayer.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const BasketballPlayer &A) {
  os << A.name+"-"+A.surname+"-"+A.position;
  return os;
}

bool BasketballPlayer::operator==(BasketballPlayer B) {
  return this->position==B.position;
}

template <class X> void print(X obj) {
    std::cout << obj << std::endl;
}