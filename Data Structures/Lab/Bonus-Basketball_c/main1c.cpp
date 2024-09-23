#include "BasketballPlayer.h"
#include "overloads.h"
#include <iostream>
using namespace std;

int main() {
cout << boolalpha;
string name, surname, position;
cin >> name >> surname >> position;
BasketballPlayer p1(name, surname, position);
cin >> name >> surname >> position;
BasketballPlayer *p2 =
new BasketballPlayer(name, surname, position);
cout << (p1 == *p2) << endl;
cout << p1 << " " << *p2 << endl;
print(1);
print("test");
print(p1);
cout << "Goodbye 1c!" << endl;
return 0;
}