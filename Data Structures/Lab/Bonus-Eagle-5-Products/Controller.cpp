#include "Controller.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Controller::save(Product products[], const char *filename, int num) {
  fstream file;
  file.open(filename, ios::out); // write
  for (int i = 0; i < num; i++) {
    file << products[i].getName() << "\n" << products[i].getPrice() << "\n";
    // copy the name and the price from array to file
  }
  file.close();
}

void Controller::load(const char *filename, Product products[], int num) {
  fstream file;
  file.open(filename, ios::in); // read
  for (int i = 0; i < num; i++) {
    string line;

    // copy the name from file to array
    getline(file, line);
    // from string to char conversion (start)
    const int length = line.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, line.c_str());
    // from string to char conversion (end)
    products[i].setName(char_array);

    // copy the price from file to array
    getline(file, line);
    products[i].setPrice(stof(line)); // from string to int conversion
  }
}