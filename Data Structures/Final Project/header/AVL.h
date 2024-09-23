#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include "../header/AVLNode.h"
#include "../header/funcs.h"

using namespace std;

class AVLTree{
    public:
        AVLTree();  // Constructor
        ~AVLTree();  // Destructor
        void createPairs(string inputFile); // inserts all the items from the file
        void searchPairs(Pair* Qset, int QsetSize); // searches pairs
        void showResults(std::string filename, Pair* Qset, int QsetSize); // shows results
        void insert(Pair pair);  // Insert a word pair into the AVL Tree
        int search(Pair pair);  // Search for a pair of contiguous words and return the number of occurrences
        void destroy();  // Destroy node from tree
        int searchValue(AVLNode* node, Pair value); // searches a value
    private:
        double constTime, searchTime;
        AVLNode* root;  // Pointer to the root node
        int getHeight(AVLNode* node);  //Get height of node
        int getBalanceFactor(AVLNode* node);  // Get the balance factor of node
        void updateHeight(AVLNode* node);  // Update the height of node
        AVLNode* rotateRight(AVLNode* node);  // Perform a right rotation on a node
        AVLNode* rotateLeft(AVLNode* node);  // Perform a left rotation on a node
        AVLNode* balanceNode(AVLNode* node);  // Balance a node
        AVLNode* insertNode(AVLNode* node, Pair pair);  // Insert a node into the AVL Tree
        AVLNode* searchNode(AVLNode* node, Pair pair);  // Search for a node in the AVL Tree
        void destroyNode(AVLNode* node); // Helper to destroy node from tree
};
#endif