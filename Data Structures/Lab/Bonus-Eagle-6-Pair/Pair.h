#ifndef PAIR_H
#define PAIR_H

#include <iostream>
using namespace std;

template <class type> class Pair {
private:
  type a;
  type b;

public:
  Pair();
  Pair(type a, type b);
  void setFirst(type a);
  void setSecond(type b);
  type getFirst();
  type getSecond();
  void swap();
  template <class X>
  friend ostream &operator<<(ostream &mystream, const Pair<X> &pair);
};

template <class type> Pair<type>::Pair() {}

template <class type> Pair<type>::Pair(type a, type b) {
  this->a = a;
  this->b = b;
}

template <class type> type Pair<type>::getFirst() { return a; }

template <class type> type Pair<type>::getSecond() { return b; }

template <class type> void Pair<type>::setFirst(type a) { this->a = a; }

template <class type> void Pair<type>::setSecond(type b) { this->b = b; }

template <class type> void Pair<type>::swap() {
  type temp = a;
  a = b;
  b = temp;
}

template <class type> ostream &operator<<(ostream &os, const Pair<type> &pair) {
  os << pair.a << "," << pair.b;
  return os;
}

#endif