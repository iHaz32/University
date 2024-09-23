#pragma once

#include <iostream>
#include <math.h>

class Point2D {
    private:
        int x;
        int y;
    public:
        Point2D() {};
        Point2D(int x, int y);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        bool operator>(Point2D &B);
        void operator=(Point2D &B);
        friend std::ostream &operator<<(std::ostream &mystream, Point2D &A);
};

Point2D::Point2D(int x, int y) {
    this->x=x;
    this->y=y;
}

void Point2D::setX(int x) {
    this->x=x;
}

void Point2D::setY(int y) {
    this->y=y;
}

int Point2D::getX() {
    return x;
}

int Point2D::getY() {
    return y;
}

bool Point2D::operator>(Point2D &B) {
    return (sqrt(this->x*this->x + this->y*this->y) > sqrt(B.x*B.x+B.y*B.y));
}

void Point2D::operator=(Point2D &B) {
    this->x=B.x;
    this->y=B.y;
}

std::ostream &operator<<(std::ostream &os, Point2D &A) {
  os << "(" << A.x << "," << A.y << ")";
  return os;
}