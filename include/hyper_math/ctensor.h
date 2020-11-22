// Rationale for splitting real-valued and complex-valued tensors:
//  users of this library, e.g. yours truly, shouldn't have to deal with complex numbers at all
//  if using FFT, the user should only be interfacing with their raw data
#pragma once
#include "fcomplex.h"

// complex valued vector
class cvec{
private:
    complexv* vec;
    bool column_vec;
    int cur_size;

public:
    cvec();
    cvec(int);
    ~cvec();

    int len();
    void transpose();
    void print_vec();

    complexv operator*(const cvec&);
    complexv& operator[](int& i) const;
    complexv& operator[](int&& i) const;
};


// complex valued matrix
class cmatrix{
private:
    cvec* matrix;
    int n;
    int m;

public:
    cmatrix();
    cmatrix(int, int);
    ~cmatrix();

    // turn matrix from n x m to m x n
    void transpose();
    void print_matrix();

    // matrix-matrix multiplication O(n^3) -> O(1) for 2x2 DFT
    cmatrix operator*(const cmatrix&);
    // matrix-vector multiplication O(nm)
    cvec operator*(const cvec&);
    cvec& operator[](int& i);
    cvec& operator[](int&& i);
};
