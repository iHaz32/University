#include "Car.h"

Car::Car() {}

Car::Car(int x, int y, std::string direction) {
    this->x = x;
    this->y = y;
    this->direction = direction;
}

void Car::setX(int x) {
    this->x = x;
}

void Car::setY(int y) {
    this->y = y;
}

void Car::setDirection(std::string direction) {
    this->direction = direction;
}

int Car::getX() const {
    return this->x;
}

int Car::getY() const {
    return this->y;
}

std::string Car::getDirection() const {
    return this->direction;
}