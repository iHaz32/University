#include "BasketballPlayer.h"
#include <iostream>
using namespace std;

int main() {
    string name, surname, position;
    cin >> name >> surname;
    Player p1(name, surname);
    cin >> name >> surname >> position;
    Player *p2 =
    new BasketballPlayer(name, surname, position);
    cout << p1.getPlayerDescription() << endl;
    cout << p2->getPlayerDescription() << endl;
    cout << "Goodbye 1b!" << endl;
    return 0;
}