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

// mt_rng::mt_rng(){

// }

// mt_rng::mt_rng(int seed){

// }
// mt_rng::~mt_rng(){

// }

// void mt_rng::twist(){
//     for(int i=0; i<max_states; i++){
//         int x = states[i] & upper_mask + states[(i+1) % max_states] & lower_mask;
//         int x_a >>= 1;
//         if(x % 2 != 0) x_a ^= a;
//         states[i] = states[(i+m) % n] ^ x_a;
//     }
//     index = 0;
// }

// unsigned int mt_rng::gen(){
//     if(index >= max_states) twist();

//     quadruple y = states[index++];
//     y ^= (y>>u) & d;
//     y ^= (y<<s) & d;
//     y ^= (y<<t) & d;
//     y ^= y>>1;

//     return (unsigned int) y & char_bits;
// }
