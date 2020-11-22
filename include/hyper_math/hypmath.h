// NOTE: cpair & cquad are basically the same classes -> abstract them out
#pragma once

typedef long double quadruple;
#define c_pi 3.14159265358979
// for extra precision. do not use for FFT
#define q_pi 3.141592653589793238462643383279502884L

// factorial -> 20! limit
long int fact(const int& x);

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
