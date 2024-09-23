#include "Controller.h"
#include "Product.h"
#include "overloads.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

  cout << fixed << setprecision(1);

  // create some example products
  Product products[3];
  char name[20];
  float price;
  for (int i = 0; i < 3; ++i) {
    cin >> name >> price;
    products[i].setName(name);
    products[i].setPrice(price);
  }

  cout << endl;

  Controller controller;

  // save the products
  controller.save(products, "products.txt", 3);

  // load the products from the file
  Product products2[3];
  controller.load("products.txt", products2, 3);

  // print the data
  for (int i = 0; i < 3; ++i) {
    cout << products2[i] << endl;
  }

  cout << "\nThank you\n";

  return 0;
}