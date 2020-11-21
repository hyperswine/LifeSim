#include "hyper_math/hypmath.h"
#include <cmath>

static quadruple rad_arr[8] {};

long int fact(const int& x){
    if(x<=1) return 1;
    int res = 0;

    for(int i=x; i>1; i++) res *= i;

    return res;
}

// 10 term series taylor approximation
// TODO: for common pi/4, pi/2, pi.. etc, returns actual
quadruple c_sin(quadruple x){
    quadruple res = 0;
    bool neg = false;
    for(int i=1; i<20; i+=2){
        res += (neg)? -pow(x, i)/fact(i): pow(x, i)/fact(i);
        neg = !neg;
    }
    return res;
}

quadruple c_cos(quadruple x){
    quadruple res = 0;
    bool neg = false;
    for(int i=0; i<20; i+=2){
        res += (neg)? -pow(x, i)/fact(i): pow(x, i)/fact(i);
        neg = !neg;
    }
    return res;
}
