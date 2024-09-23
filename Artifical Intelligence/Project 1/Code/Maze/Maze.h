#ifndef MAZE_H
#define MAZE_H

// INCLUDE FILES
#include "../car/car.h"

// INCLUDE LIBRARIES
#include <string>
#include <vector>
#include <sstream>

class Maze {
private:
    Car* cars;   // Cars stored in an array
    bool** free;   // Status of each cell
    std::string actionName;   // Action taken
    Maze* prev;   // Previous maze status

public:
    int width;   // Width of maze
    int height;   // Height of maze
    int max_cars;   // Cars in maze

    // CONSTRUCTORS
    Maze();   // Default constructor
    Maze(int width, int height);   // Constructor
    Maze(int width, int height, int max_cars, Car cars[]);   // Constructor with car parameters
    Maze(const Maze& other);   // Copy constructor

    // DESTRUCTOR
    ~Maze();   // Deallocates memory

    // SETTERS
    void setCars(Car cars[], int max_cars);   // Sets cars
    void setFree(int x, int y, bool free);   // Sets status of a cell, free or not
    void setActionName(std::string actionName);   // Sets action name
    void setPrev(Maze *prev);   // Sets previous maze status

    // GETTERS
    Car *getCars(); // Gets cars
    bool getFree(int x, int y);   // Gets if a cell is free
    std::string getActionName();   // Gets action name
    Maze *getPrev();   // Gets previous maze status
    int getDepth();   // Gets depth of maze in a tree

    // ACTIONS
    bool goUp(int carIndex, Maze &n);   // Moves a car up if possible
    bool goDown(int carIndex, Maze &n);   // Moves a car down if possible
    bool goLeft(int carIndex, Maze &n);   // Moves a car left if possible
    bool goRight(int carIndex, Maze &n);   // Moves a car right if possible
    std::vector <Maze *> expand(int carIndex);   // Makes a car move to a direction if possible

    // OVERLOADING
    bool operator==(const Maze& o) const;   // Compares mazes
    Maze& operator= (const Maze &m);   // Assigns a maze to another maze
    std::string toString ();   // Prints out maze info
};

#endif