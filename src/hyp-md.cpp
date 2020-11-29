// NOTE: maybe require types to be quadruples, in case of division by zero
#include "md.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/rng_engine.h"
#include "hyper_math/qtensor.h"
#include <iostream>
using namespace std;

const quadruple argon_eps = 3.4e-8;
const quadruple argon_sigma = 1.7e-14;

void welcome_message(){
    std::cout << "\n\t========================" << std::endl;
    std::cout << "\t  Welcome to Hyper Sim" << std::endl;
    std::cout << "\t========================" << std::endl;
}


cpair<qvec> verlet_integration(qvec& r_prev, qvec& r_i, qvec& v_i, quadruple delta){
    // initialize next pos & vel's to 0 vectors
    qvec r_next(r_i.len());
    qvec v_next(v_i.len());

    // TODO: compute accelerations by computing force potentials then taking the negative partial derivative
    qvec a_i(r_i.len());

    r_next = r_i*2 + r_prev + a_i * pow(delta,2);
    v_next = (r_next - r_prev)/(2 * delta);

    return cpair<qvec>(r_next, v_next);
}

// define one of our own energy functions
// NOTE: should probably make a MD class with this method contaning RNG
quadruple c_pot_energy(qvec r, qvec v) {
    RAND_ENG::RNG rng;
    qvec u = rng.gen_randvec(r.len());
    return (r + v) * u;
}

// LJ(r_i, r_j) = 4*eps*(del/d_ij^12 -del/d_ij^6)
quadruple lj_potential(qvec r_i, qvec r_j, quadruple eps, quadruple sigma){
    quadruple dist_ij = r_i | r_j;
    quadruple res = 4 * eps * (sigma/pow(dist_ij,12) - sigma/pow(dist_ij,6));

    return res;
}

// eps = 3.4e-8, sigma = 1.7e-14,
quadruple argon_pot(qvec r_i, qvec r_j){
    return lj_potential(r_i, r_j, argon_eps, argon_sigma);
}

// TODO: this function
// compute total forces from all particles, which is basically the partial derivative of the sum of their potential functions
// can think of it as the entire potential energy of the system
quadruple force_potential(qmatrix pos, int index){
    // for a given position to other all positions, compute potential(pos(i), pos(i+1..N))
    quadruple accum_v = 0;
    for(int i=0; i<pos.rows()-2; i++){
        for(int j=i+1; j<pos.cols()-1; j++){
            // accumulate potential(pos(i), pos(j))
            accum_v += argon_pot(pos[i], pos[j]);
        }
    }

    return accum_v;
}

//////
// TEMPORARY HELPER FUNCTIONS
///////...

// 1st order approximation. Works on both accelerations and velocities
// Will work decently on small dt
static qvec first_approx(qvec q, qvec q_prime, quadruple dt){
    // q(t+dt) = q(t) + q'(t)*dt
    return q + q_prime*dt;
}

// integrate accelerations to get velocities
static qvec verlet_accelerations(qvec accel, quadruple delta){

    return qvec();
}

// integrate velocities to get positions
static qvec verlet_velocities(qvec positions, quadruple delta){

    return qvec();
}

// adaptive runge-kutta 4th order approximation to integrate accelerations
static qvec rk4_accelerations(qvec a_j, quadruple dt=0.1){
    auto v1 = a_j * dt;
    // require a_j at t+dt/2 ? -> differentiate v at v(t) + 1/2v1
    auto v2 = a_j;

    return qvec();
}

// adaptive runge-kutta 4th order approximation to integrate velocities
static qvec rk4_velocities(qvec r_j, quadruple dt=0.1){

    return qvec();
}

// Hyper-exponential space complexity for naive algorithm. O(n^2) time complexity. Would require writing to file if can't fit everything in memory

/** 
 * Calculate the positions of all atoms over n timesteps, and returns a 3D tensor containing all positions of all atoms over the n timesteps
 * @param [ab] -> limits of cubic lattice
 * @param output_file -> True = outputs result to 'naive_md.out'
 * @param n -> timesteps and particles
 */
void naive_md(int n_particles, int n_timesteps, int a, int b, bool output_file) {
    RAND_ENG::RNG r_gen;

    // Remember that these structures are completely overwritten at each atom iteration i

    ///////
    //  INITIALIZE positions[0] to be random positions in some cubic lattic between [a, b]
    ///////

    qmatrix positions = r_gen.gen_randmatrix(n_particles, 3, a, b); // 3 -> (x, y, z) coordinates of space
    qmatrix velocities = r_gen.gen_randmatrix(n_particles, 3, a, b);
    qmatrix accelerations = r_gen.gen_randmatrix(n_particles, 3, a, b);
    qvec potentials(n_particles);
    qvec f(n_particles);
    quadruple dt = 0.1;

    ///////////
    //  CALCULATIONS of md for n timesteps
    /////////

    for (int i = 1; i <= n_timesteps; i++) {
        for (int j = 0; j < n_particles; j++) {

            // r_j = integrate velocity of current particle according to runge-kutta 4th scheme
            // positions[i][j] = first_approx(positions[i-1][j], velocities[i-1][j], dt);

            // if the position exceeds boundaries, apply reflective boundary condition, i.e. in this case simply
            // move it back in the opposite direction of limits by some factor x
            // if(boundary_condition(positions[i][j], a, b)){
            //     apply_reflective(positions[j]);
            // }

            // calculate all the forces acting on this particle
            // partial derivative of sum(V(r_jk)) where j>k
            f[j] = force_potential(positions, j);

            // calculate acceleration
            accelerations[i][j] = f[j];

            // v_(j+1) = integrate acceleration
            // velocities[i][j] = first_approx(velocities[i][j], accelerations[i][j]);

        }
    }

}
