// For complex valued operations.
// Note, these tensors (matrices and vectors) are made for complex valued operations
#pragma once
#include "hyper_math/hypmath.h"

class complexv{
private:
    quadruple a;
    quadruple b;
public:
    // numeric representation, a + ib
    complexv(quadruple, quadruple);
    // exponential representation, e^{i*theta}, where input = theta, e.g. pi
    // NOTE: theta is in radians. Do not use degrees!
    complexv(quadruple);

    void set_re(quadruple);
    void set_im(quadruple);
    quadruple re() const;
    quadruple im() const;
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

    quadruple operator*(const cv_vec&);
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
