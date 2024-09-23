#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>
#include "../header/funcs.h"

using namespace std;

class AVLNode{
    public:
        WordPair wordPair;  // Pair of contiguous words
        int height;  //Height of tree
        AVLNode *left;  // Pointer to the left subtree
        AVLNode *right;  // Pointer to the right subtree
        AVLNode(WordPair pair);  // Constructor
};
#endif