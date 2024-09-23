#pragma once

#include "Pair.h"

class Array {
    protected:
    // attributes
    int capacity, size;
    Pair* data;   // array
    double constTime, searchTime;   // performance
    // protected methods
    void doubleCapacity();
    virtual void handlePair(Pair* tempPair);
    virtual void createPairs(std::string filename);
    virtual void searchPairs(Pair* Qset, int QsetSize);

    public:
    // constructor - destructor
    Array();
    ~Array();
    // public methods
    void showResults(std::string filename, Pair* Qset, int QsetSize);
};
