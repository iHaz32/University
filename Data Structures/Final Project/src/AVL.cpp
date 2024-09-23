#include "../header/AVL.h"
#include <iostream>
#include <fstream>
#include <chrono>

//Constructor
AVLTree::AVLTree(){
    root=nullptr;
}

//Destructor
AVLTree::~AVLTree(){
    destroy();
}

//Get height of node
int AVLTree::getHeight(AVLNode* node){
    if(node==nullptr)
        return 0;
    return node->height;
}

// Get the balance factor of node
int AVLTree::getBalanceFactor(AVLNode* node){
    if (node==nullptr)
        return 0;
    return getHeight(node->left)-getHeight(node->right);
}

// Update the height of node
void AVLTree::updateHeight(AVLNode* node){
    if (node==nullptr)
        return;
    node->height=max(getHeight(node->left),getHeight(node->right))+1;
}

// Perform a right rotation on a node
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* newRoot=node->left;
    node->left=newRoot->right;
    newRoot->right=node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Perform a left rotation on a node
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* newRoot=node->right;
    node->right=newRoot->left;
    newRoot->left=node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Balance a node
AVLNode* AVLTree::balanceNode(AVLNode* node){
    updateHeight(node);
    int balanceFactor=getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Insert a node into the AVL Tree
AVLNode* AVLTree::insertNode(AVLNode* node,Pair pair) {
    if (node == nullptr)
        node = new AVLNode(pair);
    else if (pair==node->wordPair)
        node->wordPair.apps++;
    else if (pair<node->wordPair)
        node->left = insertNode(node->left, pair);
    else
        node->right = insertNode(node->right, pair);

    return balanceNode(node);
}

// Insert a word pair into the AVL Tree
void AVLTree::insert(Pair pair) {
    // Call insertNode to insert the node
    root = insertNode(root,pair);
}

// Search for a node in the AVL Tree
AVLNode* AVLTree::searchNode(AVLNode* node, Pair pair) {
    if (node==nullptr || pair==node->wordPair)
        return node;

    if (pair<node->wordPair)
        return searchNode(node->left, pair);
    else
        return searchNode(node->right, pair);
}

// Search for a pair of contiguous words and return the number of occurrences
int AVLTree::search(Pair pair) {
    //Call searchNode to search for the node
    AVLNode* result = searchNode(root, pair);
    if (result != nullptr)
        return result->wordPair.apps;
    else
        return 0;
}

// Destroy node from tree
void AVLTree::destroy() {
    destroyNode(root);
    root = nullptr;
}

// Helper to destroy node from tree
void AVLTree::destroyNode(AVLNode* node) {
    if (node == nullptr)
        return;

    destroyNode(node->left);
    destroyNode(node->right);
    delete node;
}

int  AVLTree:: searchValue(AVLNode* node, Pair value) {
    if (!node)
        return -1;
    if (node->wordPair == value)
        return node->wordPair.apps;
    if (value > node->wordPair)
        return searchValue(node->right, value);
    if (value < node->wordPair)
        return searchValue(node->left, value);
}

void AVLTree:: createPairs(std::string inputFile) {
    std::ifstream file;
    file.open(inputFile);

    if (file.is_open()) {

        auto startConstructing = std::chrono::high_resolution_clock::now();
        std::string prevWord, currWord;
        Pair *tempPair = new Pair;


        // start creating the pairs
        while (file >> currWord) {
            if (!prevWord.empty()) {
            
                Pair key(prevWord, currWord);
                insert(key);
            }
            prevWord = currWord;
        }

        auto endConstructing = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endConstructing - startConstructing;
        this->constTime = duration.count();

        file.close();

        std::ofstream output;
        output.open("results/AVL.txt");
        output << "Time to create " << size << " pairs for Binary Search Tree: " << constTime << " seconds." << std::endl; 
    } else {
        std::cerr << "Error! file not found..." << std::endl;
    }
}

void AVLTree:: searchPairs(Pair* Qset, int QsetSize) {
    std::cout<<"start search"<<std::endl;
    auto startSearching = std::chrono::high_resolution_clock::now(); 

    for (int i=0 ; i<QsetSize ; i++) {
        Qset[i].apps = searchValue(root, Qset[i]);
    }

    auto endSearching = std::chrono::high_resolution_clock::now();
    std::chrono::duration <double> duration = endSearching - startSearching;
    searchTime = duration.count();

    std::ofstream output;
    output.open("results/AVL.txt", std::ios::app);
    output << "Time to search " << QsetSize << " pairs for AVL Tree: " << searchTime << " seconds." << std::endl;

    output << std::endl << "Pairs and their number of appearances:" << std::endl;
    for (int i=0 ; i<QsetSize ; i++) {
        output << Qset[i] << std::endl;
    }
     std::cout<<"end search"<<std::endl;
}

void AVLTree:: showResults(std::string filename, Pair* Qset, int QsetSize) {
    createPairs(filename);
    searchPairs(Qset, QsetSize);
}