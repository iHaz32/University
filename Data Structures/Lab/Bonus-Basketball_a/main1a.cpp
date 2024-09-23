#include "BasketballPlayer.h"
#include <iostream>
using namespace std;

int main() {
    string name, surname, position;
    cin >> name >> surname >> position;
    BasketballPlayer p1(name, surname, position);
    cin >> name >> surname >> position;
    BasketballPlayer *p2 = new BasketballPlayer(name, surname, position);
    cout << p1.getName() << endl;
    cout << p2->getSurname() << endl;
    cout << p2->getPosition() << endl;
    cout << "Goodbye 1a!" << endl;
    return 0;
}