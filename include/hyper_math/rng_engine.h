
// Random number abstraction. 32-bits are enough for simulation
// I don't like too many things in the header file so the variable names are usually removed for methods.
#pragma once
#include "hyper_math/rng_engine.h"
#include "hyper_math/linear_alg.h"
#include <random>

// specify generation method
enum SRNG_METHOD{R_TIME, R_DCV, R_SEED};
const int USE_RD = -1;

// create namespace -> we dont want to accidentally interfere with another library
namespace RAND_ENG{

// We want a simple, fast and reliable way to generate numbers
class RNG{
private:
    int _seed;
    std::random_device _rd; // these won't be overwritten after calling constructor
    std::mt19937 generator;
public:
    RNG(SRNG_METHOD m=R_DCV, int seed=USE_RD); //note optional arg at seed=-1 -> use timer instead.
    void set_seed(int seed);

    // NOTES: if generating tensors with random values, either change to inline functions, or use this implementation
    // only use the functions below for demonstration, testing and small scale number generating

    /////////////////////////////
    //  RANDOM NUMBER GENERATION
    //////////////////////////

    int gen_int();
    int gen_int(int, int);
    quadruple gen_quad(int, int);
    quadruple gen_small_quad();

    ///////////////////////////////
    //  VECTOR & MATRIX GENERATION
    ////////////////////////////

    // generate a vector of random values, length n
    CVec gen_randvec(int);
    CMatrix gen_randmatrix(int, int);
    // generate a vector of length n, with values between [a, b]
    CVec gen_randvec(int, int, int);
    CMatrix gen_randmatrix(int, int, int, int);

};

}
