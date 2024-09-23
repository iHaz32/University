#ifndef MYFILE_H
#define MYFILE_H

class myFile {
private:
  char *name;

public:
  //Constructors
  myFile();
  myFile(char *);
  //Methods
  void setName(char *);
  char *getName();
  bool exists();
  int countLines();
  int countChars();
  //Overflows
  bool operator==(myFile f);
  myFile operator=(myFile f);
  myFile operator+=(myFile f);
};

#endif