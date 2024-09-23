#include "../header/BST.h"
#include <iostream>
#include <fstream>
#include <chrono>

// constructor
BST:: BST() {
    root = nullptr;
    size = 0;
}

// destructor
BST:: ~BST() {
    destroyTree();
}

// recursively destroy the tree
void BST:: destroyTree(Node* node) {
    if (!node)   // if node is nullptr then we are done
        return;
    // destroy left and right subtree if they exist
    if (node->left)
        destroyTree(node->left);
    if (node->right)
        destroyTree(node->right);
    delete node;
}

void BST:: insert(Pair value) {
    insertNode(root, value);
}

// insert node or increase pair's appearances
void BST:: insertNode(Node*& node, Pair value) {
    if (!node) {
        node = new Node;
        node->value = value;
        node->value.apps = 1;
        node->left = nullptr;
        node->right = nullptr;
        size++;
    } else if (value == node->value) {
        node->value.apps++;
    } else if (value > node->value) {
        insertNode(node->right, value);
    } else {
        insertNode(node->left, value);
    }
}

// store unique pairs in the tree
void BST:: createPairs(std::string filename) {
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        auto startConstructing = std::chrono::high_resolution_clock::now();
        std::string word;
        Pair *tempPair = new Pair;

        // start creating the pairs
        file >> word;
        tempPair->word1 = word;
        while (file) {
            file >> word;
            tempPair->word2 = word;
            insert(*tempPair);
            tempPair->word1 = word;
        }
        delete tempPair;

        auto endConstructing = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endConstructing - startConstructing;
        this->constTime = duration.count();

        file.close();

        std::ofstream output;
        output.open("results/BST.txt");
        output << "Time to create " << size << " pairs for Binary Search Tree: " << constTime << " seconds." << std::endl; 
    } else {
        std::cerr << "Error! file not found..." << std::endl;
    }
}

int BST:: searchValue(Node* node, Pair value) {
    if (!node)
        return -1;
    if (node->value == value)
        return node->value.apps;
    if (value > node->value)
        return searchValue(node->right, value);
    if (value < node->value)
        return searchValue(node->left, value);
}

// search the pairs using the custom searchValue function
void BST:: searchPairs(Pair* Qset, int QsetSize) {
    auto startSearching = std::chrono::high_resolution_clock::now();

    for (int i=0 ; i<QsetSize ; i++) {
        Qset[i].apps = searchValue(root, Qset[i]);
    }

    auto endSearching = std::chrono::high_resolution_clock::now();
    std::chrono::duration <double> duration = endSearching - startSearching;
    searchTime = duration.count();

    std::ofstream output;
    output.open("results/BST.txt", std::ios::app);
    output << "Time to search " << QsetSize << " pairs for Binary Search Tree: " << searchTime << " seconds." << std::endl;

    output << std::endl << "Pairs and their number of appearances:" << std::endl;
    for (int i=0 ; i<QsetSize ; i++) {
        output << Qset[i] << std::endl;
    }
}

void BST:: showResults(std::string filename, Pair* Qset, int QsetSize) {
    createPairs(filename);
    searchPairs(Qset, QsetSize);
}

void BST:: destroyTree() {
    destroyTree(root);
}
