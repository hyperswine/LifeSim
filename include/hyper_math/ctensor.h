#pragma once
#include "fcomplex.h"

// complex valued vector
class cvec{
private:
    complexv* vec;

public:
    cvec();
    cvec(int);
    ~cvec();

    double operator*(const cvec&);
    complexv& operator[](int& i);
};


// complex valued matrix
class cmatrix{
private:
    cvec* matrix;

public:
    cmatrix();
    cmatrix(int, int);
    ~cmatrix();

    cmatrix operator*(const cmatrix&);
    cvec& operator[](int& i);
};
