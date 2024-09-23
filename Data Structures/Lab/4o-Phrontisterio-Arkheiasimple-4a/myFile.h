#ifndef MYFILE_H
#define MYFILE_H

class myFile {
private:
  char *name;

public:
  myFile();
  myFile(char *);
  void setName(char *);
  char *getName();
  int countLines();
};

#endif