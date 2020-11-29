// Definition of complex numbers and operations involving them.
// cmath implements PI as a long double, so no need to redefine constants
#include "hyper_math/fcomplex.h"
#include "hyper_math/hypmath.h"
#include <cmath>
#include <iostream>

complexv::complexv(){
    a = 0;
    b = 0;
}

complexv::complexv(double x, double y){
    a = x;
    b = y;
}

complexv::complexv(double theta_rad){
    // evaluate cos(theta_rad) + i*sin(theta_rad)
    a = cos(theta_rad);
    b = sin(theta_rad);
}

complexv::complexv(complexv& to_copy){
    a = to_copy.re();
    b = to_copy.im();
}

double& complexv::re(){
    return a;
}
double& complexv::im(){
    return b;
}
void complexv::set_re(double x){
    a = x;
}
void complexv::set_im(double y){
    b = y;
}

void complexv::print() const{
    std::cout << a << " + i*" << b << std::endl;
}

complexv complexv::operator+(complexv& c2){
    complexv res(re() + c2.re(), im() + c2.im());
    return res;
}

// add the value of c2 to this value
void complexv::operator+=(complexv& c2){
    a += c2.re();
    b += c2.im();
}

complexv complexv::operator-(complexv& c2){
    complexv res(re() - c2.re(), im() - c2.im());
    return res;
}

complexv complexv::operator*(complexv& c2) const{
    // (a+bi)(x+yi) = ax - by + (ay + bx)i
    double new_a = (a * c2.re()) - (b * c2.im());
    double new_b = (a * c2.im()) + (b * c2.re());

    complexv res(new_a, new_b);
    return res;
}

// multiply both real and imaginary parts
complexv complexv::operator*(double lambda){
    complexv res(a*lambda, b*lambda);
    return res;
}

complexv complexv::operator/(complexv& c2){
    // (a+bi)/(x+yi) = conjugate -> (ax+by)/(x^2 + y^2) + i(bx-ay)/(x^2 + y^2)
    double o_top = (re() * c2.re()) + (im() * c2.im());
    double t_top =  - (re() * c2.im()) + (im() * c2.re());
    double denom = pow(c2.re(),2) + pow(c2.im(),2);

    complexv res(o_top/denom, t_top/denom);
    return res;
}

bool complexv::operator==(complexv& c2){
    return (re()==c2.re() && im()==c2.im());
}

void complexv::operator=(complexv& c2){
    a = c2.re();
    b = c2.im();
}
