#include "Customer.h"
#include <cstring>
#include <iostream>
using namespace std;
#define MAX_ITEMS 3

Customer::Customer(char *username) {
  for (int i = 0; i < MAX_ITEMS; i++) { // initialize shopping cart
    shoppingCart[i] = NULL;
  }

  this->username = new char[strlen(username) + 1]; // alocate memory
  strcpy(this->username, username);                // copy username
}

Customer::~Customer() { delete[] username; }

char *Customer::getUsername() { return username; }

int Customer::getNumberOfProducts() {
  int productsCounter = 0;
  for (int i = 0; i < MAX_ITEMS; i++) { // access shopping cart
    if (shoppingCart[i] != NULL) {      // check if item exists
      productsCounter++;
    }
  }
  return productsCounter;
}

bool Customer::addProduct(Product *product) {
  for (int i = 0; i < MAX_ITEMS; i++) { // access shopping cart
    if (shoppingCart[i] == NULL) {      // check if item exists
      shoppingCart[i] = product;
      return true;
    }
  }
  return false;
}

float Customer::getTotalCost() {
  float totalCost = 0;
  for (int i = 0; i < MAX_ITEMS; i++) { // access shopping cart
    if (shoppingCart[i] != NULL) {      // check if item exists
      totalCost += shoppingCart[i]->getPrice();
    }
  }
  return totalCost;
}

Product *Customer::findProductById(unsigned int id, int &pos) {
  for (int i = 0; i < MAX_ITEMS; i++) { // access shopping cart
    if (shoppingCart[i] != NULL && shoppingCart[i]->getId() == id) {
      pos = i;
      return shoppingCart[i];
    }
  }
  pos = -1;
  return NULL;
}

bool Customer::removeProduct(unsigned int id) {
  for (int i = 0; i < MAX_ITEMS; i++) { // access shopping cart
    if (shoppingCart[i] != NULL && shoppingCart[i]->getId() == id) {
      shoppingCart[i] = NULL;
      return true;
    }
  }
  return false;
}