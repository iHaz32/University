#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct measurement {
  char location[30];
  float temperature;
  char unit;
};

int readMeasurement(struct measurement M[]) {

  char input = ' ';
  int counter = 0;
  while (counter < 100 && input != 'q') {
    scanf(" ");
    fgets(M[counter].location, 30, stdin);
    M[counter].location[strcspn(M[counter].location, "\n")] = '\0';
    scanf("%f %c", &M[counter].temperature, &M[counter].unit);
    scanf(" %c", &input);
    counter++;
  }
  return counter;
}

int main(void) {
  struct measurement M[100];
  int i, counter = readMeasurement(M);
  double subCounter = 0, sum = 0, avg;
  char inputLocation[30], inputUnit;
  bool found = false;

  /*
  for (i = 0; i < counter; i++) {
    printf("location:%s temp:%f unit:%c\n", M[i].location,
           M[i].temperature, M[i].unit);
  }
  */

  scanf(" ");
  fgets(inputLocation, 30, stdin);
  inputLocation[strcspn(inputLocation, "\n")] = '\0';
  scanf("%c", &inputUnit);

  for (i = 0; i < counter; i++) {
    if (strcmp(inputLocation, M[i].location) == 0) {
      found = true;
      subCounter++;
      if (inputUnit == M[i].unit) {
        sum += M[i].temperature;
      } else {
        sum += inputUnit == 'c' ? (M[i].temperature - 32) * 5 / 9
                                : (M[i].temperature * 9 / 5) + 32;
      }
    }
  }

  avg = sum / subCounter;
  if (found) {
    printf("%.1lf", avg);
  } else {
    printf("0.0");
  }

  return 0;
}