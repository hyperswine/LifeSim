// For complex valued operations.
// Note, these tensors (matrices and vectors) are made for complex valued operations
#pragma once
#include "hyper_math/hypmath.h"

// complex number representation with doubles, to exploit exponentials
class complexv{
private:
    double a;
    double b;
public:
    // numeric representation, a + ib
    complexv(double, double);
    // exponential representation, e^{i*theta}, where input = theta, e.g. pi
    // NOTE: theta is in radians. Do not use degrees!
    complexv(double);

    void set_re(double);
    void set_im(double);
    double re() const;
    double im() const;
    void print() const;

    complexv operator+(const complexv&);
    complexv operator-(const complexv&);
    complexv operator*(const complexv&);
    complexv operator/(const complexv&);
    // equivalence
    bool operator==(const complexv&);
    // re-set, i.e. copy operator
    void operator=(const complexv&);

};


// complex valued vector
class cv_vec{
private:
    complexv* vec;

public:
    cv_vec();
    cv_vec(int);
    ~cv_vec();

    double operator*(const cv_vec&);
    complexv& operator[](int& i);
};


// complex valued matrix
class cv_matrix{
private:
    cv_vec* matrix;

public:
    cv_matrix();
    cv_matrix(int, int);
    ~cv_matrix();

    cv_matrix operator*(const cv_matrix&);
    cv_vec& operator[](int& i);
};
