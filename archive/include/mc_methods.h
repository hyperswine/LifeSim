// monte carlo algorithm declarations. May not be required.
#pragma once
#include "hmath"

quadruple sample_I(const qvec& input);
quadruple sample_mc_integral(int n_gen);
quadruple mc_integral(int n_gen);

// Metropolis algorithm -> markov process sampling. 
// Generates m states from a sequential distribution. Basically maps from {states} at a time t to a single state.
hvec<> metropolis_alg(hmatrix<>);
