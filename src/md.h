#pragma once
#include "hyper_math/qtensor.h"
#include <any>

void do_execute();
void welcome_message();

// local search energy estimation
// for an atoms position and energy, calculate its lowest energy state with local search
// WARNING: prone to local minima. Lowest energy state not guaranteed.
quadruple local_search();

////////
//  Required Functions
////////

// The verlet integration method uses 3rd order taylor expansions (error in the order of del^4)
// We use this function at every timestep to find the positions 
// In - prev, current positions & velocities of a particle i, at some timestep 0 <= t < n_timesteps
cpair<qvec> verlet_integration(qvec&, qvec&, qvec&, quadruple);

/**
 * In - positions of particle i & particle j
 * Out - potential energy between i & j as a result of their distance
 */
quadruple lj_potential(qvec, qvec, quadruple eps, quadruple sigma);
quadruple argon_pot(qvec, qvec);

// NAIVE MD Method
// - no multithreading
// - no list optimizations
// - records positions of all particles at every timestep, instead of at every x timesteps

qmatrix naive_md(int n_particles, int n_timesteps, bool output_file);
qmatrix naive_md(int n_particles, int n_timesteps, int a, int b, bool output_file);
