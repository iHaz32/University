# pragma once

#include <iostream>
#include "Pair.h"

// helper class which's objects will be stored in our hashtable
class hashEntry {
    public:
    // attributes
    Pair pair;
    unsigned long long int hashCode;
    bool occupied;   // shows if a cell has data
    // constructor
    hashEntry() {occupied = false;}
};

class HashTable {
    protected:
    // attributes
    hashEntry* data;
    unsigned long long int size, capacity;
    int hashFunction(hashEntry key, int capacity);
    double constTime, searchTime;   // performance
    // private helper methods
    void createPairs(std::string filename);
    void searchPairs(Pair* Qset, int QsetSize);
    // private methods
    void doubleSize();
    void handlePair(Pair tempPair);
    unsigned long long int createHashCode(Pair tempPair);

    public:
    // constructor - destructor
    HashTable();
    ~HashTable();
    // methods
    void showResults(std::string filename, Pair* Qset, int QsetSize);
};