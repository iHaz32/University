// include header files
#include "../header/Pair.h"

// bool overloads 
bool operator==(Pair& p1, Pair& p2) {
    return (p1.word1 == p2.word1) && (p1.word2 == p2.word2);
}

bool operator>(Pair& p1, Pair& p2) {
    return (p1.word1 > p2.word1) || (p1.word1 == p2.word1 && p1.word2 > p2.word2);
}

bool operator>=(Pair& p1, Pair& p2) {
    return (p1.word1 > p2.word1) || (p1.word1 == p2.word1 && p1.word2 >= p2.word2);
}

bool operator<(Pair& p1, Pair& p2) {
    return (p1.word1 < p2.word1) || (p1.word1 == p2.word1 && p1.word2 < p2.word2);
}

bool operator<=(Pair& p1, Pair& p2) {
    return (p1.word1 < p2.word1) || (p1.word1 == p2.word1 && p1.word2 <= p2.word2);
}

// output overload
std::ostream& operator<<(std::ostream& os, Pair& p) {
    os << "[" << "{" << p.word1 << ", " << p.word2 << "} " << "apps: " << p.apps << "]";
    return os;
}
