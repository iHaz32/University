#include <iostream>
#include <string.h>
using namespace std;

/**
 * @brief Helper function for determining what test case to run, based on the
 * main arguments
 *
 * @param testName
 * @param numOfRequestedTests
 * @param argv
 * @return true
 * @return false
 */
bool shouldRun(const char *testName, int numOfRequestedTests,
               char const *argv[]) {
  // no tests provided as parameters, therefore run all tests
  if (numOfRequestedTests == 0)
    return true;

  for (int i = 0; i < numOfRequestedTests; i++) {
    // argv[i + 1] -> skip first item...
    if (strcmp(testName, argv[i + 1]) == 0)
      return true;
  }
  return false;
}

/**
 * @brief Helper function for printing a label and a text
 *
 * @tparam T
 * @param label The label to be printed
 * @param text The text to be printed
 */
template <typename T> void print(const char *label, const T &text) {
  cout << "TEST::" << label << " >> " << text << endl;
}