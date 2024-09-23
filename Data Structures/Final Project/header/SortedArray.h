#pragma once

#include "Array.h"

class SortedArray : public Array {
    protected:
    // protected methods
    void handlePair(Pair* tempPair);
    int binarySearchPair(Pair tempPair);
    void createPairs(std::string filename);
    void searchPairs(Pair *Qset, int QsetSize);
};