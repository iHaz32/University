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
  if (name!=NULL) { //if it points somewhere, delete its content
    delete[] name;
  }
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
}

char *myFile::getName() { return name; }

bool myFile::exists() {
  fstream file;
  file.open(name, ios::in);
  return file.is_open();
}

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

int myFile::countChars() {
  fstream file;
  file.open(name, ios::in);
  if (file.is_open()) {
    string line;
    int counter = 0;
    while (getline(file, line)) {
      counter+=line.length();
    }
    const int lines = this->countLines();
    file.close();
    return counter+lines; // include line breaks ("\n")
  } else {
    return 0;
  }
}

bool myFile::operator==(myFile f) {
  fstream file1, file2;
  file1.open(name, ios::in);
  file2.open(f.getName(), ios::in);
  if (file1.is_open() && file2.is_open()) {
    string line1;
    string line2;
    do {
      getline(file1, line1);
      getline(file2, line2);
    } while (!(line1.compare(line2) || file1.eof() || file2.eof())); //continue if you havent found any difference and files are still not done, algebra Bool is used to simplify this logical expression
    file1.close();
    file2.close();
    return !line1.compare(line2); //return their last compare which defines if the files are same (function returns 0 when same)
  } else {
    return false;
  }
}

myFile myFile::operator=(myFile f) {
  fstream file1, file2;
  file1.open(name, ios::out); //write
  file2.open(f.getName(), ios::in);
  string line;
  while (getline(file2, line)) {
    file1 << line << "\n";
  }
  file1.close();
  file2.close();
  return *this;
}

myFile myFile::operator+=(myFile f) {
  fstream file1, file2;
  file1.open(name, ios::app); //append
  file2.open(f.getName(), ios::in);
  string line;
  while (getline(file2, line)) {
    file1 << line << "\n";
  }
  file1.close();
  file2.close();
  return *this;
}