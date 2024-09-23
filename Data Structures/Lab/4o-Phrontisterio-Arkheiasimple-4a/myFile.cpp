#include "myFile.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

myFile::myFile() {
  this->name = new char[5]; //"NULL\0"
  strcpy(name, "NULL");
}

myFile::myFile(char *name) {
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}

void myFile::setName(char *name) {
  delete[] name;
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}

char *myFile::getName() { return name; }

int myFile::countLines() {
  fstream file;
  file.open(name, ios::in); // read
  if (file.is_open()) {
    string line;
    int counter = 0;
    while (getline(file, line)) {
      counter++;
    }
    file.close();
    return ++counter; // include last empty line
  } else {
    return 0;
  }
}