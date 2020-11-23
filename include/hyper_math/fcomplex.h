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
    double& re();
    double& im();
    void print() const;

    complexv operator+(complexv&);
    void operator+=(complexv&);
    complexv operator-(complexv&);
    complexv operator*(complexv&) const;
    complexv operator/(complexv&);
    // equivalence
    bool operator==(complexv&);
    // re-set, i.e. copy operator
    void operator=(complexv&);

};
