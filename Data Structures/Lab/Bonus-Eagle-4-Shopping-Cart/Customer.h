#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Product.h"

#include <iostream>
using namespace std;

// max cart items
#define MAX_ITEMS 3

class Customer {
private:
  // Every customer has a username
  char *username;

  // Every customer has a cart with up to 3 products
  Product *shoppingCart[MAX_ITEMS];

  // The next free position in the shopping cart (initially this is 0)
  // int pos;

public:
  // Constructor
  Customer(char *username);

  // Destructor
  ~Customer();

  /**
   * @brief Getter for the username
   *
   * @return char* The name of the customer
   */
  char *getUsername();

  /**
   * @brief Returns the number of products in the cart (initially this is 0)
   *
   * @return int The number of the products in the cart
   */
  int getNumberOfProducts();

  /**
   * @brief Function for adding a product to the cart.
   *
   * @param product The pointer to the product that we want to add to the cart
   * @return true If the product has been successfully added to the cart
   * @return false If the cart is full
   */
  bool addProduct(Product *product);

  /**
   * @brief Returns the total cost of the products in the cart (initially this
   * is 0)
   *
   * @return float The total cost of the cart
   */
  float getTotalCost();

  /**
   * @brief Returns the pointer to the product with the specified id in the
   * cart, along with its position (pos)
   *
   * @param id The id of the product we are trying to find
   * @param pos If the product is found, pos contains the position of the
   * product in the cart
   * @return Product* If the product is found in the cart, the pointer to this
   * product is returned. If the product is not in the cart, NULL is
   * returned and pos=-1.
   */
  Product *findProductById(unsigned int id, int &pos);

  /**
   * @brief Removes a product from the cart
   *
   * @param id The id of the product tha we want to remove
   * @return true If the product has been successfully removed from the cart
   * @return false If the product is not in the cart or the cart is empty
   */
  bool removeProduct(unsigned int id);
};

#endif