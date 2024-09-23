#pragma once

#include <vector>

template <class X> class Comparator {
    private:
        std::vector<X> x;
        std::vector<X> y;
    public:
        Comparator(std::vector<X>, std::vector<X>);
        bool equals();
};

template <class X> Comparator<X>:: Comparator(std::vector<X> x, std::vector<X> y) {
  this->x = x;
  this->y = y;
}

template <class X> bool Comparator<X>:: equals() {
    if (this->x.size()!=this->y.size()) {
        return false;
    }
    for (int i=0;i<this->x.size();i++) {
        if (!(x[i]==y[i])) {
            return false;
        }
    }
    return true;
}