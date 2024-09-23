#ifndef PERSON_H
#define PERSON_H

class Person {
protected:
  int id;
  char surname[100];

public:
  void setId(int);
  void setSurname(char *);
  int getId();
  char *getSurname();
  Person();
  Person(int, char *);
  ~Person();
};

#endif