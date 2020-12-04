// Here we demonstrate the integration method of randomized 'dart throwing' to approximate
// the volume of an n-dimensional object.
#include "hyper_math/hypmath.h"
#include "hyper_math/qtensor.h"
#include "hyper_math/rng_engine.h"
#include "mc_methods.h"
#include <any>
#include <cmath>

using namespace std;
using namespace RAND_ENG;

// The function f(x0, x1, x2...) that maps to some a real number r
quadruple sample_I(const qvec& input){
    // in this sample, we map n input values into a 3-period of sin(x_0) + cos(x_1) + ..
    quadruple sum = 0;

    for(int i=0; i< input.len(); i++){
        // if(i%2==0) sum += sin(input[i]);
        // else sum += cos(input[i]);
    }

    return sum;
}


// The function f(x0, x1, x2...) that maps to some a real number r
quadruple hard_sample_I(const qvec& input){
    // in this sample, we map n input values into a 3-period of sin(x_0) + cos(x_1) + tan(x_3) + sin(x_4) +...
    quadruple sum = 0;

    for(int i=0; i< input.len(); i++){
        // if(i%3==0)
        //     sum += sin(input[i]);
        // else if(i%3==1)
        //     sum += cos(input[i]);
        // else
        //     sum += tan(input[i]);
    }

    return sum;
}

// Randomly generate numbers in the n-dimensional rectangle
quadruple sample_mc_integral(int n_gen){
    // sample function takes k args
    int d_input = 10;
    // choose a set of random values between [a, b]
    RNG _rng;
    qvec out(n_gen); //output points (f(x) vals)

    // generate random points in d-hypercube
    // for(int i=0; i<n_gen; i++){
    //     qvec in = _rng.gen_randvec(d_input, -1, 1);
    //     out[i] = sample_I(in);
    // }
    
    // check how many in points have f(x) <= y
    // e.g. out[i] <= sample_I(in)

    return 0.0;
}


