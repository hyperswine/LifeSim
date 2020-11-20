#pragma once
#include "hyper_math/linear_alg.h"

void do_execute();
void welcome_message();

// local search energy estimation
// for an atoms position and energy, calculate its lowest energy state with local search
// WARNING: prone to local minima. Lowest energy state not guaranteed.
double local_search();

////////
//  Required Functions
////////

/**
 * In - positions of particle i & particle j
 * Out - potential energy between i & j as a result of their distance
 */
double lj_potential(CVec, CVec);

// NAIVE MD Method
// - no multithreading
// - no list optimizations
// - records positions of all particles at every timestep, instead of at every x timesteps

CMatrix naive_md(int n_particles, int n_timesteps, bool output_file);
CMatrix naive_md(int n_particles, int n_timesteps, int a, int b, bool output_file);
