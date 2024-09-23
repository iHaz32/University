// INCLUDE FILES
#include "maze/maze.h"

// INCLUDE LIBRARIES
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>

// FUNCTION THAT PRINTS THE MAZE IN A VIRTUAL WAY
void graph(Maze* initial) {
    for (int y = 0; y < initial->height; y++) {
        for (int x = 0; x < initial->width; x++) {
            if (initial->getFree(x, y)) {
                std::cout << " F ";   // Free
            } else {
                bool isCar = false;
                int k;

                // Checks if the non-free cell is a car
                for (k = 0; k < initial->max_cars; k++) {
                    if (initial->getCars()[k].getX() == x && initial->getCars()[k].getY() == y) {
                        isCar = true;
                        break;
                    }
                }

                if (isCar)
                    std::cout << " C" << k;   // Car with index
                else
                    std::cout << " B ";   // Barrier
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// BFS FUNCTION
Maze* BFS(Maze *initial, Maze *final, long long &examined, long long &totalNodes) {
    std::queue<Maze *> agenda;   // Agenda is queue due to BFS
    std::vector <Maze> closed;   // Stores visited nodes
    Maze *s;   // Represents current maze status

    // Initialization
    examined = 0;   // Visited nodes
    totalNodes = 1;   // Total nodes of tree, starting from the root
    int carIndex = 0;   // Current car index

    agenda.push(initial);   // Gets the initial maze status

    while (agenda.size() > 0 && carIndex < initial->max_cars) {   // As long as agenda is not empty and at least one car is inside the maze
        s = agenda.front();   // Gets the front element of queue
        agenda.pop();   // Removes the front elemnt of queue

        if (find(closed.begin(), closed.end(), *s) == closed.end()) {   // Visits the node if it is not already visited
            std::cout << "Move " << examined << ": (" << s->getActionName() << ")" <<std::endl;   // Helper message
            graph(s);   // Graph of maze
            examined++;   // Increases visited nodes
            closed.push_back(*s);   // Adds the node to the visited nodes
            std::vector<Maze *> children =s->expand(carIndex);   // Expands the node and store its children
            for (unsigned int i = 0; i < children.size(); i++) {   // Iterates through children
                totalNodes++;   // Increases total nodes count
                if (children[i]->getCars()[carIndex].getX() == -1 || children[i]->getCars()[carIndex].getY() == -1 ||children[i]->getCars()[carIndex].getX() == initial->width || children[i]->getCars()[carIndex].getY() == initial->height)  {   // Checks if a children is a solution
                    // Sets coordinates to (-1, -1) to follow the admissions
                    children[i]->getCars()[carIndex].setX(-1);
                    children[i]->getCars()[carIndex].setY(-1);

                    carIndex++;   // Goes to next car
                    if (carIndex == initial->max_cars) {   // If the last remaining car is out
                        s = children[i];   // Sets the current maze status as the children status which is the final and start the loop again which will exit
                        std::cout << "Move " << examined << ": (" << s->getActionName() << ")" <<std::endl;   // Helper message
                        graph(s);   // Graph of maze
                        continue;   // Repeats the loop which will exit
                    }
                }
                if (find(closed.begin(), closed.end(), *children[i]) == closed.end())   // Adds child to agenda if it is not already visited
                    agenda.push(children[i]);
            }
        }
    }
    if (*s==*final)   // Checks if final state of BFS is equal to the target state
        return s;   // Returns the final state
    return nullptr;    // Returns null pointer otherwise
}

// FUNCTIONS THAT CREATE THE THREE MAZES
Maze** first();
Maze** second();
Maze** third();

// MAIN FUNCTION
int main() {
    long long examined, totalNodes;

    for (int n = 0; n < 3; n++) {
        Maze** mazes;
        if (n == 0) mazes = first();   // First problem
        if (n == 1) mazes = second();   // Second problem
        if (n == 2) mazes = third();   // Third problem

        Maze *initial = mazes[0];   // Initial state
        Maze *final = mazes[1];   // Final - goal state

        // SHOWS INITIAL STATE
        std::cout << n + 1 << ". Initial state: " << std::endl << initial->toString() << std::endl;   // Print initial state

        Maze *sol;   // Result of BFS
        sol = BFS(initial, final, examined, totalNodes);   // Run BFS and collect stats

        // SHOWS STATS
        if (sol != nullptr)
            std::cout<<"Depth of BFS tree: "<< sol->getDepth()<< ", Examined Nodes: "<< examined << ", Total Nodes Discovered: " << totalNodes << std::endl << std::endl << std::endl;
        else
            std::cout<<"Problem is unsolvable!" << std::endl << std::endl << std::endl;

        // DEALLOCATES MEMORY
        delete mazes[0];
        delete mazes[1];
        delete[] mazes;
    }
}

// CREATES FIRST MAZE
Maze** first() {
    int max_cars = 2;   // Starting number of cars

    Car initialCars[max_cars];   // Initial states of cars
    Car finalCars[max_cars];   // Final states of cars - goal states
    
    Maze i(3,2);   // Initial state of maze
    Maze f(3,2);   // Final state of maze - goal state

    // SETS COORDINATES OF CARS AND BARRIERS
    initialCars[0].setX(1);
    initialCars[0].setY(0);
    initialCars[0].setDirection("W/E");
    i.setFree(1, 0, false);

    initialCars[1].setX(2);
    initialCars[1].setY(1);
    initialCars[1].setDirection("N/S");
    i.setFree(2, 1, false);

    i.setFree(0, 0, false);
    i.setFree(1, 1, false);

    // CREATES FINAL STATES OF CARS
    for (int i = 0; i < max_cars; i++) {
        finalCars[i].setX(-1);
        finalCars[i].setY(-1);
        finalCars[i].setDirection(initialCars[i].getDirection());
    }
  
    // SETTING UP MAZES
    i.setCars(initialCars, max_cars);
    f.setCars(finalCars, max_cars);

    Maze** mazes = new Maze*[2];
    mazes[0] = new Maze(i);
    mazes[1] = new Maze(f);

    return mazes;
}

// CREATES SECOND MAZE
Maze** second() {
    int max_cars = 3;   // Starting number of cars

    Car initialCars[max_cars];   // Initial states of cars
    Car finalCars[max_cars];   // Final states of cars - goal states
    
    Maze i(4,3);   // Initial state of maze
    Maze f(4,3);   // Final state of maze - goal state

    // SETS COORDINATES OF CARS AND BARRIERS - EXAMPLE OF ASSIGNMENT
    initialCars[0].setX(2);
    initialCars[0].setY(0);
    initialCars[0].setDirection("W/E");
    i.setFree(2, 0, false);
    
    initialCars[1].setX(2);
    initialCars[1].setY(1);
    initialCars[1].setDirection("N/S");
    i.setFree(2, 1, false);

    initialCars[2].setX(1);
    initialCars[2].setY(1);
    initialCars[2].setDirection("W/E");
    i.setFree(1, 1, false);

    i.setFree(0, 1, false);
    i.setFree(2, 2, false);
    i.setFree(3, 0, false);

    // CREATES FINAL STATES OF CARS
    for (int i = 0; i < max_cars; i++) {
        finalCars[i].setX(-1);
        finalCars[i].setY(-1);
        finalCars[i].setDirection(initialCars[i].getDirection());
    }
  
    // SETTING UP MAZES
    i.setCars(initialCars, max_cars);
    f.setCars(finalCars, max_cars);

    Maze** mazes = new Maze*[2];
    mazes[0] = new Maze(i);
    mazes[1] = new Maze(f);

    return mazes;
}

// CREATES THIRD MAZE
Maze** third() {
    int max_cars = 6;   // Starting number of cars

    Car initialCars[max_cars];   // Initial states of cars
    Car finalCars[max_cars];   // Final states of cars - goal states
    
    Maze i(6,6);   // Initial state of maze
    Maze f(6,6);   // Final state of maze - goal state

    // SETS COORDINATES OF CARS AND BARRIERS
    initialCars[0].setX(2);
    initialCars[0].setY(0);
    initialCars[0].setDirection("W/E");
    i.setFree(2, 0, false);

    initialCars[1].setX(2);
    initialCars[1].setY(1);
    initialCars[1].setDirection("N/S");
    i.setFree(2, 1, false);

    initialCars[2].setX(1);
    initialCars[2].setY(1);
    initialCars[2].setDirection("W/E");
    i.setFree(1, 1, false);

    initialCars[3].setX(3);
    initialCars[3].setY(2);
    initialCars[3].setDirection("W/E");
    i.setFree(3, 2, false);

    initialCars[4].setX(1);
    initialCars[4].setY(2);
    initialCars[4].setDirection("W/E");
    i.setFree(1, 2, false);

    initialCars[5].setX(4);
    initialCars[5].setY(4);
    initialCars[5].setDirection("W/E");
    i.setFree(4, 4, false);

    i.setFree(0, 1, false);
    i.setFree(2, 2, false);
    i.setFree(3, 0, false);
    i.setFree(0, 3, false);
    i.setFree(1, 3, false);
    i.setFree(5, 4, false);
    i.setFree(3, 5, false);
    i.setFree(4, 5, false);

    // CREATES FINAL STATES OF CARS
    for (int i = 0; i < max_cars; i++) {
        finalCars[i].setX(-1);
        finalCars[i].setY(-1);
        finalCars[i].setDirection(initialCars[i].getDirection());
    }
  
    // SETTING UP MAZES
    i.setCars(initialCars, max_cars);
    f.setCars(finalCars, max_cars);

    Maze** mazes = new Maze*[2];
    mazes[0] = new Maze(i);
    mazes[1] = new Maze(f);

    return mazes;
}