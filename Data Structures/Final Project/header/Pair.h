# pragma once

#include <iostream>

struct Pair {
    std::string word1, word2;
    int apps;

    Pair() {};
    Pair(std::string a, std::string b) {word1=a; word2=b;}
};

// bool overloads
bool operator==(Pair& p1, Pair& p2);
bool operator>(Pair& p1, Pair& p2);
bool operator>=(Pair& p1, Pair& p2);
bool operator<(Pair& p1, Pair& p2);
bool operator<=(Pair& p1, Pair& p2);
// stream overloads
std::ostream& operator<<(std::ostream& os, Pair& p);
