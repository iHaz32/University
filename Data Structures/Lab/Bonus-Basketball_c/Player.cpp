#include "Player.h"
#include <string>

Player:: Player(std::string name, std::string surname) {
    this->name = name;
    this->surname = surname;
}

std::string Player:: getName() {
    return this->name;
}

std::string Player:: getSurname() {
    return this->surname;
}

std::string Player:: getPlayerDescription() {
    return this->name+"-"+this->surname;
}