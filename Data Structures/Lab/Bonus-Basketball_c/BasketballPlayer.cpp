#include "BasketballPlayer.h"
#include <string>

BasketballPlayer:: BasketballPlayer(std::string name, std::string surname, std::string position) {
    this->name=name;
    this->surname=surname;
    this->position=(position.length()<3)?"unknown":position;
}

std::string BasketballPlayer:: getPosition() {
    return this->position;
}

std::string BasketballPlayer:: getPlayerDescription() {
    return this->name+"-"+this->surname+"-"+this->position;
}