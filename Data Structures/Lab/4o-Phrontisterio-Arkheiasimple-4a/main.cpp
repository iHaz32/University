#include "myFile.h"
#include <iostream>
using namespace std;

int main() {
  char s1[30];
  cin >> s1;
  myFile a(s1);

  char s2[30];
  cin >> s2;
  myFile b(s2);

  myFile c((char *)"temp.txt");
  cout << "Lines in file A: " << a.countLines() << endl;
  cout << "Lines in file B: " << b.countLines() << endl;
  cout << "Lines in file C: " << c.countLines() << endl;

  return 0;
}