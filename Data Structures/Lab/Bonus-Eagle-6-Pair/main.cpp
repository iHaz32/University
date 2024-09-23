#include "Pair.h"
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main() {
  Pair<int> a(13, 25);
  Pair<string> b;
  string s;

  a.setFirst(a.getFirst() - 1);
  a.setSecond(a.getSecond() + 1);
  a.swap();

  cin >> s;
  b.setFirst(s);
  cin >> s;
  b.setSecond(s);
  b.swap();

  cout << a << endl << b << endl;
  cout << "Thank you!\n";
  return 0;
}