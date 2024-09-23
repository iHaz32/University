#include "ymd_converter.h"
#include <stdio.h>

time_t YMD_to_time(const char *ymd) {
    if (ymd == NULL) {
        return (time_t)-1;
    }

    struct tm tm = {0}; // Important: initialize all members to 0
    int n = 0;
    sscanf(ymd, "%4d-%2d-%2d %n", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &n);

    // Scan incomplete or extra junk?
    if (n == 0 || ymd[n]) {
        return (time_t)-1; // Mal-formed string
    }

    // Could add extra checks for months/days outside primary range, spaces in string, etc.

    // Adjust ranges as struct tm uses different references
    tm.tm_year -= 1900;
    tm.tm_mon--;
    tm.tm_isdst = -1; // Important to get right time for Year-Month-Day 00:00:00 _local time_

    // The following conversion assumes tm is in local time.
    return mktime(&tm); // This may return -1;
}