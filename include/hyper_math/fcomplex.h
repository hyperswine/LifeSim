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
    complexv();
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
    void operator+=(const complexv&);
    complexv operator-(const complexv&);
    complexv operator*(const complexv&) const;
    complexv operator/(const complexv&);
    // equivalence
    bool operator==(const complexv&);
    // re-set, i.e. copy operator
    void operator=(const complexv&);

};
