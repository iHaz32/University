#ifndef CAR_H
#define CAR_H

// INCLUDE LIBRARIES
#include <string>

class Car {
private:
    int x, y;   // Coordinates of the car
    std::string direction;   // Direction of the car, "N/S" or "W/E"

public:
    // CONSTRUCTORS
    Car();   // Default constructor
    Car(int x, int y, std::string direction);   // Constructor with parameters

    // SETTERS
    void setX(int x);   // Sets x
    void setY(int y);   // Sets y
    void setDirection(std::string direction);   // Sets direction

    // GETTERS
    int getX() const;   // Gets x
    int getY() const;   // Gets y
    std::string getDirection() const;   // Gets direction
};

#endif