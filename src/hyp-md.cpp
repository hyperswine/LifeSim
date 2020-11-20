// NOTE: maybe require types to be quadruples, in case of division by zero
#include "md.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/rng_engine.h"
#include "hyper_math/linear_alg.h"
#include <iostream>
using namespace std;

void welcome_message(){
    std::cout << "\n\t========================" << std::endl;
    std::cout << "\t  Welcome to Hyper Sim" << std::endl;
    std::cout << "\t========================" << std::endl;
}

// define one of our own energy functions
// NOTE: should probably make a MD class with this method contaning RNG
double c_pot_energy(CVec r, CVec v) {
    RAND_ENG::RNG rng;
    CVec u = rng.gen_randvec(r.len());
    return (r + v) * u;
}

/**
 * LJ(r_i, r_j) = 4(1/d_ij^12 - 1/d_ij^6)
 */ 
double lj_potential(CVec r_i, CVec r_j){
    double dist_ij = r_i | r_j;
    double res = 4 * (1/pow(dist_ij,12) - 1/pow(dist_ij,6));

    return res;
}


// Hyper-exponential space complexity for naive algorithm. O(n^2) time complexity. Would require writing to file if can't fit everything in memory

// default [a, b] = [-1, 1]
CMatrix naive_md(int n_particles, int n_timesteps, bool output_file);

/** 
 * Calculate the positions of all atoms over n timesteps, and returns a 3D tensor containing all positions of all atoms over the n timesteps
 */
CMatrix naive_md(int n_particles, int n_timesteps, int a, int b, bool output_file) {
    RAND_ENG::RNG r_gen;

    // Remember that these structures are completely overwritten at each atom iteration i

    ///////
    //  INITIALIZE positions[0] to be random positions in some cubic lattic between [a, b]
    ///////

    CMatrix positions = r_gen.gen_randmatrix(n_particles, 3, a, b); // 3 -> (x, y, z) coordinates of space
    CMatrix velocities = r_gen.gen_randmatrix(n_particles, 3, a, b);
    CMatrix accelerations = r_gen.gen_randmatrix(n_particles, 3, a, b);
    CVec potentials(n_particles);
    CVec f(n_particles);

    ///////////
    //  CALCULATIONS of md for n timesteps
    /////////

    for (int i = 0; i < n_timesteps; i++) {
        for (int j = 0; j < n_particles; j++) {
            // v[j] = integrate accelerations
            // r[j] = integrate velocities

            // potentials[j] = energy(r)
        }
    }

    return CMatrix(1, 1);
}
