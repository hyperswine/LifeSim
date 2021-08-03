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

// duplicate a three-dimensional system into mirrored images of 9 parallel boxes


// NAIVE MD Method
// - no multithreading
// - no list optimizations
// - records positions of all particles at every timestep, instead of at every x timesteps
void naive_md(int n_particles, int n_timesteps, int a=-1, int b=1, bool output_file=true);

// simulation in a two-dimensional simulation plane.
// is a decent approximation for specific types of materials, e.g. compounds in catalysis
qmatrix md_2d();

/**
 * In - N three-dimension vectors of all positions
 * Out - Lower triangular matrix of potentials 
 */
void particle_ewald();
