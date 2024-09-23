#include "../header/AVLNode.h"
#include <iostream>
#include <string>

using namespace std;

AVLNode::AVLNode(Pair pair){
    this->wordPair=pair;
    wordPair.apps=1;
    this->height=1;
    this->left=nullptr;
    this->right=nullptr;
}