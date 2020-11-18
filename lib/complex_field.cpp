// Define complex numbers and operations involvng them.
#include "hyper_math/complex_field.h"
#include <math.h>

ComplexV::ComplexV(double x, double y){
    a = x;
    b = y;
}

ComplexV ComplexV::operator+(const ComplexV& c2){
    ComplexV res(re() + c2.re(), im() + c2.im());
    return res;
}

ComplexV ComplexV::operator-(const ComplexV& c2){
    ComplexV res(re() - c2.re(), im() - c2.im());
    return res;
}

ComplexV ComplexV::operator*(const ComplexV& c2){
    // (a+bi)(x+yi) = ax - by + (ay + bx)i
    double new_a = (re() * c2.re()) - (im() * c2.im());
    double new_b = (re() * c2.im()) + (im() * c2.re());

    ComplexV res(new_a, new_b);
    return res;
}

ComplexV ComplexV::operator/(const ComplexV& c2){
    // (a+bi)/(x+yi) = conjugate -> (ax+by)/(x^2 + y^2) + i(bx-ay)/(x^2 + y^2)
    double o_top = (re() * c2.re()) + (im() * c2.im());
    double t_top =  - (re() * c2.im()) + (im() * c2.re());
    double denom = pow(c2.re(),2) + pow(c2.im(),2);

    ComplexV res(o_top/denom, t_top/denom);
    return res;
}

bool ComplexV::operator=(const ComplexV& c2){
    return (re()==c2.re() && im()==c2.im());
}
