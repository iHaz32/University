#ifndef DATE_H
#define DATE_H

class Date {
private:
  int date;
  int month;
  int year;

public:
  Date();
  Date(int, int, int);
  void setDate(int);
  int getDate();
  void setMonth(int);
  int getMonth();
  void setYear(int);
  int getYear();
  int daysInMonth(int m);
  void add(int k);
  int diff(Date b);
};

#endif