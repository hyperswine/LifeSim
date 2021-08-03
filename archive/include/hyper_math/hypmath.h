// NOTE: cpair & cquad are basically the same classes -> abstract them out
#pragma once
#include <string>

typedef long double quadruple;
#define c_pi 3.14159265358979
// for extra precision. do not use for FFT
#define q_pi 3.141592653589793238462643383279502884L

const int OUT_OF_BOUNDS = -1;
const int UNSYMMETRIC_SIZE = -2;
const int TOO_LARGE = -3;
const int MEMORY_ERROR = -4;
const int INVALID_OP = -5;
const int STACK_LIMIT = 50000; // Arbitrary Limit: we should not be storing anything more than this value in a vector
const int DEFAULT_THREADS = 16;

typedef struct _odd_even{
    bool even = true;
} ODD_EVEN;

// factorial -> 20! limit
long int fact(const int& x);

// pth root -> 18 s.f. Uses 'shifting nth root algorithm'
inline quadruple p_root(quadruple x, int p);

inline quadruple abs_r(quadruple r_i, quadruple r_j);

// trig functions based on taylor series expansion of 10 terms
double c_sin(double);
double c_cos(double);

template <class T> class cpair{
private:
    T x;
    T y;

public:
    cpair(T& a, T& b){
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

template <class T> class cquad{
private:
    T* _t;

public:
    cquad(T& a, T& b, T& c, T& d){
        _t = new T[4];
        _t[0] = a;
        _t[1] = b;
        _t[2] = c;
        _t[3] = d;
    }
    ~cquad(){
        delete[] _t;
    }

    // the main selling point -> not going over array bounds
    T& operator[](int i){
        int indexer = i % 4;
        return _t[indexer];
    }

    T* begin(){
        return _t;
    }

    T* end(){
        return _t + 4;
    }

    bool operator==(cpair<T> &oth_t){
        for(int i=0; i<4; i++)
            if (_t[i] != oth_t[i]) return false;

        return true;
    }
};

// cpair but takes two different classes
template <class T1, class T2> class fpair{
private:
    T1 x;
    T2 y;

public:
    fpair(T1& a, T2& b){
        x = a;
        y = b;
    }

    T1 get_first(){
        return x;
    }

    T2 get_second(){
        return y;
    }

    bool operator==(fpair<T1, T2> &oth_t){
        return (x == oth_t[0] && y == oth_t[1]);
    }
};

const unsigned int max_val = 0xFFFFFFFF;
const unsigned int char_bits = 0x0000000F;

/**
 * CREDIT: Wikipedia for providing pseudocode for mersenne twister.
 */ 
// class mt_rng{
// private:
//     size_t max_states;
//     // vector containing max. states (recurrences). Default value = 1000
//     qvec* states;
//     size_t index;
//     // r = 4 bits (char = 1byte)
//     unsigned int lower_mask = (1 << 4) - 1;
//     // take bits 0..3
//     unsigned int upper_mask = (~lower_mask) & (char_bits);

//     void twist();

// public:
//     mt_rng();
//     // provide an initial seed (int). Note if wanting to use clock time, random device, etc.
//     // must first extract an integer
//     mt_rng(int seed);
//     ~mt_rng();

//     // generate a value from the mersenne twister
//     unsigned int gen();
    
// };
