#include "hyper_math/rng_engine.h"
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

void RNG::set_seed(unsigned int seed){
    if (seed == USE_RD){
        std::random_device* rd = new std::random_device();
        // NOTE: apparently some errors with this?
        // generator.seed(rd);
    }
    else{
        // generator.seed(seed);
    }
    
    _seed = seed;
}

// generates a double between 0-1
double RNG::gen_double(){
    // generate an int, then return inverse
    return (double) 1 / generator();
}

// generates an int between 0-2.14b
int RNG::gen_int(){
    return 0;
}

// generates an int in the closed range [a, b]
int RNG::gen_int(int a, int b){
    using namespace std;
    // std::uniform_int_distribution dist(a, b);

    // return dist(generator);
    return 0;
}
