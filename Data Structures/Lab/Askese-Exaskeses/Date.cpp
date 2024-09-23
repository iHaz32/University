#include "Date.h"

Date::Date() {
  date = 0;
  month = 0;
  year = 0;
}

Date::Date(int date, int month, int year) {
  this->date = date;
  this->month = month;
  this->year = year;
}

void Date::setDate(int date) { this->date = date; }

int Date::getDate() { return date; }

void Date::setMonth(int month) { this->month = month; }

int Date::getMonth() { return month; }

void Date::setYear(int year) { this->year = year; }

int Date::getYear() { return year; }

int Date::daysInMonth(int m) {
  if (m == 2) {
    return 28;
  }
  if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
    return 31;
  } else {
    return 30;
  }
}

void Date::add(int k) {
  int limit = daysInMonth(month);
  if (date + k > limit) {
    date = limit - date + 2;
    if (month == 12) {
      month = 1;
      year++;
    } else {
      month++;
    }
  } else {
    date += k;
  }
}

int Date::diff(Date b) {
  int tempDateB = b.getDate(), tempMonthB = b.getMonth(),
      tempYearB = b.getYear(), dayDiff, monthDiff, yearDiff,
      monthDiffToDays = 0, i;
  if (b.getDate() < date) {
    tempDateB = b.getDate() + daysInMonth(b.getMonth());
    tempMonthB--;
  }
  if (b.getMonth() < month) {
    tempMonthB += 12;
    tempYearB = b.getYear() - 1;
  }
  dayDiff = tempDateB - date;
  monthDiff = tempMonthB - month;
  for (i = month; i < tempMonthB; i++) {
    monthDiffToDays += daysInMonth(i);
  }
  yearDiff = tempYearB - year;
  return dayDiff + monthDiffToDays + yearDiff * 365;
}