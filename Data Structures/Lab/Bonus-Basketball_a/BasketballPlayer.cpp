#include "BasketballPlayer.h"
#include <string>

BasketballPlayer:: BasketballPlayer(std::string name, std::string surname, std::string position) {
    this->name=name;
    this->surname=surname;
    this->position=position;
}

std::string BasketballPlayer:: getPosition() {
    return this->position;
}