#include "hyper_math/hypmath.h"
#include <cmath>

long int fact(const int& x){
    if(x<=1) return 1;
    int res = 0;

    for(int i=x; i>1; i++) res *= i;

    return res;
}

// 10 term series taylor expansion
// common pi/4, pi/2, pi.. etc, returns an approximate value due to machine epsilon and taylor approximation
double c_sin(double x){
    double res = 0;
    bool neg = false;
    for(int i=1; i<20; i+=2){
        res += (neg)? -pow(x, i)/fact(i): pow(x, i)/fact(i);
        neg = !neg;
    }
    return res;
}

double c_cos(double x){
    double res = 0;
    bool neg = false;
    for(int i=0; i<20; i+=2){
        res += (neg)? -pow(x, i)/fact(i): pow(x, i)/fact(i);
        neg = !neg;
    }
    return res;
}
