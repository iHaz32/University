#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Customer.h"
#include "test_lib.h" // helpers for tests

using namespace std;

// Helper printer for products. It prints the id, the name and the price.
void printProduct(Product *p) {
  cout << "TEST::Product{id:" << p->getId() << ", name:" << p->getName()
       << ", price:" << p->getPrice() << "}" << endl;
}

// Helper printer for customers. It prints the username, the number of products
// in their cart and its total cost.
void printCustomer(Customer *c) {
  cout << "TEST::Customer{username:" << c->getUsername()
       << ", number of products:" << c->getNumberOfProducts()
       << ", total cost:" << c->getTotalCost() << "}" << endl;
}

// Declaration of test cases
void testCreateProduct();  // 1
void testCreateCustomer(); // 2
void testAddProduct();     // 3
void testFindProduct();    // 4
void testRemoveProduct();  // 5

// Max size of string values read as input
const unsigned int BUFFER_SIZE = 1024;

/*
 * The main function. It gets as a parameter the test cases to run. If no
 * parameter is provided, all test cases will run.
 * Example: > ./main.exe testCreateCustomer testAddProduct
 */
int main(int argc, char const *argv[]) {
  // The numbers will be printed with 1 decimal digit by default (see here
  // https://www.cplusplus.com/reference/ios/fixed/)
  cout << fixed << setprecision(1);

  // For printing true or false instead of 1 or 0
  cout << boolalpha;

  // Check what tests to run, based on main arguments.
  // If testCreateProduct has been provided as parameter, then run it.
  if (shouldRun("testCreateProduct", argc - 1, argv))
    testCreateProduct();

  // If testCreateCustomer has been provided as parameter, then run it.
  if (shouldRun("testCreateCustomer", argc - 1, argv))
    testCreateCustomer();

  // If testAddProduct has been provided as parameter, then run it.
  if (shouldRun("testAddProduct", argc - 1, argv))
    testAddProduct();

  // If testFindProduct has been provided as parameter, then run it.
  if (shouldRun("testFindProduct", argc - 1, argv))
    testFindProduct();

  // If testRemoveProduct has been provided as parameter, then run it.
  if (shouldRun("testRemoveProduct", argc - 1, argv))
    testRemoveProduct();

  cout << "_____TESTS COMPLETED_____" << endl;

  return 0;
}

/******************************************************************
***************************** Test Case 1 *************************
******************************************************************/
void testCreateProduct() {
  cout << "_____TEST CREATE PRODUCT_____" << endl;

  cout << "Give a product id: " << endl;
  unsigned int _id;
  cin >> _id;

  cout << "Give a product name: " << endl;
  char *_name = new char[BUFFER_SIZE];
  cin >> _name;

  float _price;
  cout << "Give a product price: " << endl;
  cin >> _price;

  Product *p = new Product(_id, _name, _price);
  printProduct(p);

  delete[] _name;
  delete p;

  cout << endl;
}
/******************************************************************/

/******************************************************************
***************************** Test Case 2 *************************
******************************************************************/
void testCreateCustomer() {
  cout << "_____TEST CREATE CUSTOMER_____" << endl;

  cout << "Give a customer username: " << endl;
  char *_username = new char[BUFFER_SIZE];
  cin >> _username;

  Customer *c = new Customer(_username);
  printCustomer(c);

  delete[] _username;
  delete c;

  cout << endl;
}
/******************************************************************/

/******************************************************************
***************************** Test Case 3 *************************
******************************************************************/
void testAddProduct() {
  cout << "_____TEST ADD PRODUCT_____" << endl;

  cout << "Give a customer username: " << endl;
  char *_username = new char[BUFFER_SIZE];
  cin >> _username;
  Customer *c = new Customer(_username);

  unsigned int _id;
  char *_name = new char[BUFFER_SIZE];
  float _price;

  cout << "Give the id, name and price of product 1: " << endl;
  cin >> _id >> _name >> _price;
  Product *p1 = new Product(_id, _name, _price);
  printProduct(p1);
  print("product added", c->addProduct(p1));
  cout << endl;

  cout << "Give the id, name and price of product 2: " << endl;
  cin >> _id >> _name >> _price;
  Product *p2 = new Product(_id, _name, _price);
  printProduct(p2);
  print("product added", c->addProduct(p2));
  cout << endl;

  printCustomer(c);
  cout << endl;

  Product *p3 = new Product(3, (char *)"something", 1.5);
  printProduct(p3);
  print("product added", c->addProduct(p3));
  cout << endl;

  // this should not be added (cart size is 3)
  Product *p4 = new Product(6, (char *)"unknown", 0.75);
  printProduct(p4);
  print("product added", c->addProduct(p4));
  cout << endl;

  printCustomer(c);

  delete c;
  delete p4;
  delete[] _username;
  delete[] _name;

  cout << endl;
}

/******************************************************************
***************************** Test Case 4 *************************
******************************************************************/
void testFindProduct() {
  cout << "_____TEST FIND PRODUCT_____" << endl;

  cout << "Give a customer username: " << endl;
  char *_username = new char[BUFFER_SIZE];
  cin >> _username;
  Customer *c = new Customer(_username);

  unsigned int _id1, _id2;
  char *_name = new char[BUFFER_SIZE];
  float _price;

  cout << "Give the id, name and price of product 1: " << endl;
  cin >> _id1 >> _name >> _price;
  Product *p1 = new Product(_id1, _name, _price);
  printProduct(p1);
  print("product added", c->addProduct(p1));
  cout << endl;

  cout << "Give the id, name and price of product 2: " << endl;
  cin >> _id2 >> _name >> _price;
  Product *p2 = new Product(_id2, _name, _price);
  printProduct(p2);
  print("product added", c->addProduct(p2));
  cout << endl;

  int _pos;
  Product *_p = c->findProductById(_id1, _pos);
  print("product id", _p->getId());
  print("found", _p != NULL);
  print("position", _pos != -1);
  cout << endl;

  _p = NULL;
  _p = c->findProductById(_id2, _pos);
  print("product id", _p->getId());
  print("found", _p != NULL);
  print("position", _pos != -1);
  cout << endl;

  _p = NULL;
  _p = c->findProductById(0, _pos); // _p should be null
  print("product id", 0);
  print("found", _p != NULL);
  print("position", _pos != -1);

  delete c;
  delete[] _username;
  delete[] _name;

  cout << endl;
}
/******************************************************************/

/******************************************************************
***************************** Test Case 5 *************************
******************************************************************/
void testRemoveProduct() {
  cout << "_____TEST REMOVE PRODUCT_____" << endl;

  cout << "Give a customer username: " << endl;
  char *_username = new char[BUFFER_SIZE];
  cin >> _username;
  Customer *c = new Customer(_username);

  unsigned int _id1, _id2;
  char *_name = new char[BUFFER_SIZE];
  float _price;

  cout << "Give the id, name and price of product 1: " << endl;
  cin >> _id1 >> _name >> _price;
  Product *p1 = new Product(_id1, _name, _price);
  printProduct(p1);
  print("product added", c->addProduct(p1));
  cout << endl;

  cout << "Give the id, name and price of product 2: " << endl;
  cin >> _id2 >> _name >> _price;
  Product *p2 = new Product(_id2, _name, _price);
  printProduct(p2);
  print("product added", c->addProduct(p2));
  cout << endl;

  Product *p3 = new Product(1111, (char *)"product3", 1.0);
  printProduct(p3);
  print("product added", c->addProduct(p3));
  cout << endl;

  printCustomer(c);
  cout << endl;

  print("product id:0 removed", c->removeProduct(0)); // false
  cout << endl;

  int pos;
  print("product 1 removed", c->removeProduct(_id1));              // true
  print("product 1 found", c->findProductById(_id1, pos) != NULL); // false
  printCustomer(c);
  cout << endl;

  print("product 1 removed", c->removeProduct(_id1));              // false
  print("product 1 found", c->findProductById(_id1, pos) != NULL); // false
  printCustomer(c);
  cout << endl;

  print("product 2 removed", c->removeProduct(_id2));              // true
  print("product 2 found", c->findProductById(_id2, pos) != NULL); // false
  printCustomer(c);
  cout << endl;

  print("product 3 removed", c->removeProduct(1111));              // true
  print("product 3 found", c->findProductById(1111, pos) != NULL); // false
  printCustomer(c);

  delete c;

  cout << endl;
}
/******************************************************************/