#include "hyper_math/hypmath.h"

template <class T> class cpair{
private:
    T x;
    T y;

public:
    cpair(T a, T b){
        x = a;
        y = b;
    }

    // works for all ints
    T operator[](int i){
        int indexer = i % 2;
        return (indexer == 0) ? x : y;
    }

    // only works for T objects with '==' operator
    bool operator==(cpair<T> &oth_t){
        return (x == oth_t[0] && y == oth_t[1]);
    }
};
