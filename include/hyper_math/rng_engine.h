#pragma once
#include <random>

    // specify generation method

enum SRNG_METHOD{
    R_TIME, R_DCV, R_SEED
    };
const int USE_RD = -1;

namespace RAND_ENG{

// We want a simple, fast and reliable way to generate numbers
class RNG{
private:
    // 32-bits are enough for simulation
    int _seed; // if _seed = -1, then use random device.
    // std::random_device* _rd;
    std::mt19937 generator;
public:
    RNG(SRNG_METHOD m=R_DCV, int seed=USE_RD); //note optional arg at seed=-1 -> use timer instead.
    // note these setters need to all be const
    void set_seed(unsigned int seed);
    // void set_seed(std::random_device* r_device) {_seed = USE_RD; generator->seed(r_device);}

    int gen_int();
    int gen_int(int, int);
    double gen_double();
};

}
