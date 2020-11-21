// Definition of complex numbers and operations involving them.
// cmath implements PI as a long double, so no need to redefine constants
#include "hyper_math/complex_field.h"
#include <cmath>
#include <iostream>

complexv::complexv(quadruple x, quadruple y){
    a = x;
    b = y;
}

complexv::complexv(quadruple theta_rad){
    // evaluate cos(theta_rad) + i*sin(theta_rad)
    a = cos(theta_rad);
    b = sin(theta_rad);
}

quadruple complexv::re() const{
    return a;
}
quadruple complexv::im() const{
    return b;
}
void complexv::set_re(quadruple x){
    a = x;
}
void complexv::set_im(quadruple y){
    b = y;
}

void complexv::print() const{
    std::cout << a << " + i*" << b << std::endl;
}

complexv complexv::operator+(const complexv& c2){
    complexv res(re() + c2.re(), im() + c2.im());
    return res;
}

complexv complexv::operator-(const complexv& c2){
    complexv res(re() - c2.re(), im() - c2.im());
    return res;
}

complexv complexv::operator*(const complexv& c2){
    // (a+bi)(x+yi) = ax - by + (ay + bx)i
    quadruple new_a = (re() * c2.re()) - (im() * c2.im());
    quadruple new_b = (re() * c2.im()) + (im() * c2.re());

    complexv res(new_a, new_b);
    return res;
}

complexv complexv::operator/(const complexv& c2){
    // (a+bi)/(x+yi) = conjugate -> (ax+by)/(x^2 + y^2) + i(bx-ay)/(x^2 + y^2)
    quadruple o_top = (re() * c2.re()) + (im() * c2.im());
    quadruple t_top =  - (re() * c2.im()) + (im() * c2.re());
    quadruple denom = pow(c2.re(),2) + pow(c2.im(),2);

    complexv res(o_top/denom, t_top/denom);
    return res;
}

bool complexv::operator==(const complexv& c2){
    return (re()==c2.re() && im()==c2.im());
}
