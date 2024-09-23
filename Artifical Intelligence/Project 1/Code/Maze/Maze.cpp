#include "Maze.h"

#include <iostream>

Maze::Maze() {}

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;

    // Allocate memory
    this->free = new bool*[height];
    for (int i = 0; i < this->height; ++i) {
        free[i] = new bool[this->width];
    }

    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
            free[y][x] = true;

    setActionName("Initialized");   // Initial state
    setPrev(nullptr);   // No parent
}

Maze::Maze(int width, int height, int max_cars, Car cars[]) {
    this->width = width;
    this->height = height;
    this->max_cars = max_cars;

    // Allocate memory
    this->free = new bool*[height];
    for (int i = 0; i < this->height; ++i) {
        free[i] = new bool[this->width];
    }

    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
            free[y][x] = true;

    setActionName("Initialized");   // Initial state
    setPrev(nullptr);   // No parent

    // Allocate memory
    this->cars = new Car[max_cars];
    for (int i = 0; i < max_cars; ++i) {
        this->cars[i] = cars[i];
    }
}

Maze::Maze(const Maze& other) {
    width = other.width;
    height = other.height;
    max_cars = other.max_cars;

    // Allocate memory
    free = new bool*[height];
    for (int i = 0; i < height; ++i) {
        free[i] = new bool[width];
        std::copy(other.free[i], other.free[i] + width, free[i]);   // Copy cells
    }
    // Allocate memory
    cars = new Car[max_cars];
    std::copy(other.cars, other.cars + max_cars, cars);   // Copy cars

    actionName = other.actionName;   // Copy action name
    prev = other.prev;   // Copy parent
}


Maze::~Maze() {
    // Deallocate memory
    for (int i = 0; i < height; ++i) {
        delete[] free[i];
    }
    delete[] free;
    delete[] cars;
}


void Maze::setCars(Car cars[], int max_cars) {
    this->max_cars = max_cars;
    this->cars = new Car[max_cars];
    for (int i = 0; i < max_cars; ++i) {
        this->cars[i] = cars[i];
    }
}

void Maze::setFree(int x, int y, bool free) {
    if (y >= 0 && y < height && x >= 0 && x < width)   // Secures to stay in bounds
        this->free[y][x] = free;
}

void Maze::setActionName(std::string actionName) {
    this->actionName = actionName;
}

void Maze::setPrev(Maze *p) {
    this->prev = p;
}

Car* Maze::getCars() {
    return this->cars;
}

bool Maze::getFree(int x, int y) {
    if (y >= 0 && y < height && x >= 0 && x < width)   // Secures to stay in bounds
        return this->free[y][x];
    return false;
}

std::string Maze::getActionName() {
    return this->actionName;
}

Maze* Maze::getPrev() {
    return this->prev;
}

int Maze::getDepth() {
    int depth = 0;
    Maze *prev = this;
    while (prev != nullptr) {   // As long as the node is not the root visit the parent and increase depth by one
        prev = prev->prev;
        depth++;
    }
    return depth;
}

bool Maze::goUp(int carIndex, Maze &n) {
    Car car = this->cars[carIndex];
    if ((getFree(car.getX(), car.getY() - 1)  || car.getY() - 1 < 0) && car.getDirection() == "N/S") {   // Secure that the targeted cell is free or out of maze and move as long it is allowed based on car direction
        n = *this;   // New state copies previous state
        car.setY(car.getY() - 1);   // Changes coordinates of car
        n.setActionName("Up");   // Changes the action name
        n.cars[carIndex] = car;   // Replaces the old state of the car with the current one
        n.setPrev(this);   // Changes parent node
        n.setFree(car.getX(), car.getY(), false);   // New cell gets not free
        n.setFree(car.getX(), car.getY() + 1, true);   // Old cell gets free
        return true;   // Moved successfully
    }
    return false;   // Did not manage to move
}

bool Maze::goDown(int carIndex, Maze &n) {
    Car car = this->cars[carIndex];
    if ((getFree(car.getX(), car.getY() + 1) || car.getY() + 1 >= height) && car.getDirection() == "N/S") {   // Secure that the targeted cell is free or out of maze and move as long it is allowed based on car direction
        n = *this;   // New state copies previous state
        car.setY(car.getY() + 1);   // Changes coordinates of car
        n.setActionName("Down");   // Changes the action name
        n.cars[carIndex] = car;   // Replaces the old state of the car with the current one
        n.setPrev(this);   // Changes parent node
        n.setFree(car.getX(), car.getY(), false);   // New cell gets not free
        n.setFree(car.getX(), car.getY() - 1, true);   // Old cell gets free
        return true;   // Moved successfully
    }
    return false;   // Did not manage to move
}

bool Maze::goLeft(int carIndex, Maze &n) {
    Car car = this->cars[carIndex];
    if ((getFree(car.getX() - 1, car.getY())  || car.getX() - 1 < 0) && car.getDirection() == "W/E") {   // Secure that the targeted cell is free or out of maze and move as long it is allowed based on car direction
        n = *this;   // New state copies previous state
        car.setX(car.getX() - 1);   // Changes coordinates of car
        n.setActionName("Left");   // Changes the action name
        n.cars[carIndex] = car;   // Replaces the old state of the car with the current one
        n.setPrev(this);   // Changes parent node
        n.setFree(car.getX(), car.getY(), false);   // New cell gets not free
        n.setFree(car.getX() + 1, car.getY(), true);   // Old cell gets free
        return true;   // Moved successfully
    }
    return false;   // Did not manage to move
    
}

bool Maze::goRight(int carIndex, Maze &n) {
    Car car = this->cars[carIndex];
    if ((getFree(car.getX() + 1, car.getY()) || car.getX() + 1 >= width) && car.getDirection() == "W/E") {   // Secure that the targeted cell is free or out of maze and move as long it is allowed based on car direction
        n = *this;   // New state copies previous state
        car.setX(car.getX() + 1);   // Changes coordinates of car
        n.setActionName("Right");   // Changes the action name
        n.cars[carIndex] = car;   // Replaces the old state of the car with the current one
        n.setPrev(this);   // Changes parent node
        n.setFree(car.getX(), car.getY(), false);   // New cell gets not free
        n.setFree(car.getX() - 1, car.getY(), true);   // Old cell gets free
        return true;   // Moved successfully
    }
    return false;   // Did not manage to move
}

std::vector <Maze *> Maze::expand(int carIndex) {
    std::vector <Maze *> children;   // Vector of children - possible moves
    Maze *child;

    child = new Maze(*this);
    if (goUp(carIndex, *child)) {   // Tries to go up
        children.push_back(child);   // Adds the child to the children vector if it manages to go up
    } else {
        delete child;
    }

    child = new Maze(*this);
    if (goDown(carIndex, *child)) {   // Tries to go down
        children.push_back(child);   // Adds the child to the children vector if it manages to go down
    } else {
        delete child;
    }

    child = new Maze(*this);
    if (goRight(carIndex, *child)) {   // Tries to go right
        children.push_back(child);   // Adds the child to the children vector if it manages to go right
    } else {
        delete child;
    }

    child = new Maze(*this);
    if (goLeft(carIndex, *child)) {   // Tries to go left
        children.push_back(child);   // Adds the child to the children vector if it manages to go left
    } else {
        delete child;
    }

    return children;
}


bool Maze::operator==(const Maze& s) const {
    // Compares coordinates and directions of each car to determine if mazes are the same
    for (int i = 0; i < max_cars; i++)
        if (this->cars[i].getX() != s.cars[i].getX() || this->cars[i].getY() != s.cars[i].getY() || this->cars[i].getDirection() != s.cars[i].getDirection())
            return false;
    return true;
}

Maze& Maze::operator=(const Maze& other) {
    if (this != &other) { // Checks for self-assignment
        // Deallocates old memory
        for (int i = 0; i < height; ++i) {
            delete[] free[i];
        }
        delete[] free;
        delete[] cars;

        // Copies new properties
        width = other.width;
        height = other.height;
        max_cars = other.max_cars;

        free = new bool*[height];
        for (int i = 0; i < height; ++i) {
            free[i] = new bool[width];
            std::copy(other.free[i], other.free[i] + width, free[i]);
        }

        cars = new Car[max_cars];
        std::copy(other.cars, other.cars + max_cars, cars);

        actionName = other.actionName;
        prev = other.prev;
    }
    return *this;
}

std::string Maze::toString() {
    std::stringstream ot;
    for (int i = 0; i < max_cars; i++)
        ot << "Car " << i << ": (X=" << this->cars[i].getX() << ", Y=" << this->cars[i].getY() << ") - " << this->cars[i].getDirection() << std::endl;   // Details for each car
    return ot.str();
}