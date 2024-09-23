#include "BasketballPlayer.h"
#include "Comparator.h"
#include "overloads.h"
#include "string"
#include <iostream>

using namespace std;

int main() {
  cout << boolalpha;

  vector<int> vect11, vect12;
  int temp;
  cin >> temp;
  while (temp >= 0) {
    vect11.push_back(temp);
    cin >> temp;
  }
  cin >> temp;
  while (temp >= 0) {
    vect12.push_back(temp);
    cin >> temp;
  }
  Comparator<int> c1(vect11, vect12);
  cout << c1.equals() << endl;

  vector<BasketballPlayer> vect21, vect22;
  string pos;
  cin >> pos;
  while (pos != "q") {
    BasketballPlayer p("", "", pos);
    vect21.push_back(p);
    cin >> pos;
  }
  cin >> pos;
  while (pos != "q") {
    BasketballPlayer p("", "", pos);
    vect22.push_back(p);
    cin >> pos;
  }
  
  Comparator<BasketballPlayer> c2(vect21, vect22);
  cout << c2.equals() << endl;

  cout << "Goodbye 1d!" << endl;

  return 0;
}