// NOTE: maybe require types to be quadruples, in case of division by zero
#include "md.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/rng_engine.h"
#include "hyper_math/linear_alg.h"
#include <iostream>
using namespace std;

const quadruple argon_eps = 3.4e-8;
const quadruple argon_sigma = 1.7e-14;

void welcome_message(){
    std::cout << "\n\t========================" << std::endl;
    std::cout << "\t  Welcome to Hyper Sim" << std::endl;
    std::cout << "\t========================" << std::endl;
}


cpair<CVec> verlet_integration(CVec& r_prev, CVec& r_i, CVec& v_i, quadruple delta){
    // initialize next pos & vel's to 0 vectors
    CVec r_next(r_i.len());
    CVec v_next(v_i.len());

    // TODO: compute accelerations using a potential function
    CVec a_i(r_i.len());

    r_next = r_i*2 + r_prev + a_i * pow(delta,2);
    v_next = (r_next - r_prev)/(2 * delta);

    return cpair<CVec>(r_next, v_next);
}

// define one of our own energy functions
// NOTE: should probably make a MD class with this method contaning RNG
quadruple c_pot_energy(CVec r, CVec v) {
    RAND_ENG::RNG rng;
    CVec u = rng.gen_randvec(r.len());
    return (r + v) * u;
}

// LJ(r_i, r_j) = 4*eps*(del/d_ij^12 -del/d_ij^6)
quadruple lj_potential(CVec r_i, CVec r_j, quadruple eps, quadruple sigma){
    quadruple dist_ij = r_i | r_j;
    quadruple res = 4 * eps * (sigma/pow(dist_ij,12) - sigma/pow(dist_ij,6));

    return res;
}

// eps = 3.4e-8, sigma = 1.7e-14,
quadruple argon_pot(CVec r_i, CVec r_j){
    return lj_potential(r_i, r_j, argon_eps, argon_sigma);
}


// Hyper-exponential space complexity for naive algorithm. O(n^2) time complexity. Would require writing to file if can't fit everything in memory

// default [a, b] = [-1, 1]
CMatrix naive_md(int n_particles, int n_timesteps, bool output_file);

/** 
 * Calculate the positions of all atoms over n timesteps, and returns a 3D tensor containing all positions of all atoms over the n timesteps
 * @param [ab] -> limits of cubic lattice
 * @param output_file -> True = outputs result to 'naive_md.out'
 * @param n -> timesteps and particles
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
