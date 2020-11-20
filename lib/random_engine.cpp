#include "hyper_math/rng_engine.h"
#include "hyper_math/linear_alg.h"
#include <chrono>

using namespace RAND_ENG;

RNG::RNG(SRNG_METHOD s_method, int seed){
    //type R_TIME -> based on time
    if (s_method == R_TIME){
        using namespace std::chrono;
        unsigned int s = system_clock::now().time_since_epoch().count();
        set_seed(s);
    }
    //type R_DCV -> based on a random device
    else if (s_method == R_DCV){
        set_seed(USE_RD);
    }
    //type R_SEED -> based on custom seed
    else{
        set_seed(seed);
    }
}

void RNG::set_seed(int seed){
    generator.seed((seed == USE_RD)? _rd(): seed);
    _seed = seed;
}

// generate a quadruple between [a, b]
quadruple RNG::gen_quad(int a, int b){
    using namespace std;
    std::uniform_real_distribution<quadruple> dist(a, b);

    return dist(generator);
}

// generates a very small quadruple between 0-1, usually skewed towards 0
quadruple RNG::gen_small_quad(){
    // generate an int, then return inverse
    return (quadruple) 1 / generator();
}

// generates an int between 0-2.14b
int RNG::gen_int(){
    return generator();
}

// generates an int in the closed range [a, b]
int RNG::gen_int(int a, int b){
    using namespace std;
    std::uniform_int_distribution dist(a, b);

    return dist(generator);
}

CVec RNG::gen_randvec(int length){
    // make sure to use random device
    set_seed(USE_RD);

    CVec res(length);
    for(int i=0; i<length; i++){
        res[i] = generator();
    }

    return res;
}

CVec RNG::gen_randvec(int length, int a, int b){
    std::uniform_int_distribution dist(a, b);

    CVec res(length);
    for(int i=0; i<length; i++){
        res[i] = dist(generator);
    }

    return res;
}

CMatrix RNG::gen_randmatrix(int n, int m){
    set_seed(USE_RD);

    CMatrix res(n, m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            res[i][j] = generator();
        }
    }

    return res;
}

// args (n, m, a, b)
CMatrix RNG::gen_randmatrix(int n, int m, int a, int b){
    std::uniform_int_distribution dist(a, b);

    CMatrix res(n, m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            res[i][j] = dist(generator);
        }
    }

    return res;
}