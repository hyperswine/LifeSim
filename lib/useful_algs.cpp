#include "hmath"
#include "mc_methods.h"

#include <utility>

#define MIN(a,b) (a > b) ? a : b

////////////////////////////////
//  GENERAL AUX. FUNCTIONS
////////////////////////////////

/**
 * Algorithm:
 *  for i = 0..min(n rows, m cols)
 *      let p = -|M[i]| -- unsure
 *      z = M[i] - p*e_1  -- where e_1 is the [1,0...0] basis vector
 *      v = 1/||z|| * z
 *      Q_i = I - 2*v*v.T
 *      M = Q_i * M
 */
// hmatrix<>* householder_qr(hmatrix<> M){
//     hmatrix<>* res = new hmatrix<>[2];
//     int _min = MIN(M.dim()[0], M.dim()[1]);
//     hmatrix<> M_p(M);
//     // e_1 is the first basis vector
//     hvec<> e_1(_min);
//     e_1[0] = 1;
//     hmatrix<> I(M.dim()[0], M.dim()[0]);
//     hmatrix<> Q(M.dim()[0], M.dim()[0]);

//     for (int i = 0; i < _min; i++){
//         // TODO: overload | operator -> for the k-norm
//         int p = -M_p[i]|1;
//         hvec z = M_p[i] - p*e_1;
//         hvec v = 1/z|2 * z;
//         quadruple v_hy = 2 * (v,v.T());

//         hmatrix<> Q_i = I - (I * v_hy);
//         if(i == 0) Q = Q_i;
//         Q *= Q_i;
//         M_p = Q_i * M;
//     }

//     // NOTE: M_p = R, and  Q^T = [Q1 Q2 ... Qmin]
//     res[0] = Q.T();
//     res[1] = M_p;
//     return res;
// }
// basically a householder_qr that splits Q = Q1*Q2 through qr again
void null_space_qr();


// Calculates the singular value decomposition of a matrix M
// 1. find row eigenvectors of (M.T*M).T -> column [v1, v2, ...vn] for V.T
// 2. find eigenvalues of (M.T*M).T -> square root and diagonlize in order of highest to lowest, for SIGMA
// 3. find Null Space of M.T and |Null Space(M.T)| -> U = [1/sigma_1, 1/sigma_2, ...1/sigma_n]
// Then we have M = U * SIGMA * V.T
void svd(hmatrix<quadruple> M){
    // QU method for eigenvalues and eigenvectors?

    // QR or Gaussian decomposition for Null Space
}

/**
 * Useful for generating a random state from a vector of states each with a probability
 * In - A vector of probabilities, each being between (0, 1)
 * Out - A cumulative distribution starting from i=0 to i=n-1
 */
static hvec<> gen_cumulative_dist(hvec<> weighted_states){
    hvec cumulative_states(weighted_states.len());
    quadruple cumulative_sum = 0;

    for(int i=0; i<weighted_states.len(); i++){
        cumulative_sum += weighted_states(i);
        cumulative_states(i) = cumulative_sum;
    }

    return cumulative_states;
}

/**
 * Generate a state s, where s in [0, 1...n] sfrom a cumulative distribution c.
 */
static quadruple gen_state(hvec<> c_dist){
    RAND_ENG::RNG rng;
    quadruple sample_weight = rng.gen_quad(0, 1);
    quadruple sample = 0;

    for(int i=0; i<c_dist.len(); i++){
        if(c_dist(i) <= sample_weight){
            sample = i;
            break;
        }
    }

    return sample;
}

/**
 * A sample function that maps R -> R, making a normally distributed targe density
 */
static quadruple norm_density(){
    return 0;
}

/**
 * An efficient sampling of a search space. For highly dense areas, have higher chance to stay,
 * for lowly dense areas, likely to move to another state. Result is a reasonable approximation
 * of some density function.
 * NOTE: test on the normal distribution.
 */
hvec<> metropolis_alg(hvec<> states, hmatrix<> m_dist, int n_samples){
    // generate an initial state i, where states[i] = probability of that state
    hvec<> c_states = gen_cumulative_dist(states);
    int curr_state = gen_state(c_states);
    RAND_ENG::RNG rng;

    // states that are going to be sampled
    hvec<> sampled_states(n_samples);

    for(int i=0; i<n_samples; i++){
        // generate another state, from m_dist[current_state]
        hvec<> next_possible_states = m_dist[i];
        auto s_dist = gen_cumulative_dist(next_possible_states);
        int next_state = gen_state(s_dist);

        // acceptance ratio
        quadruple acceptance_r = (norm_density(next_state)) / (norm_density(curr_state));

        quadruple num = rng.gen_quad(0, 1);
        // if acceptance ratio is at most a randomly generated value between [0, 1], then accept and transition to new state
        // else stay at current state
        if(acceptance_r <= num){
            curr_state = next_state;
        }
        
    }
}

// randomized min cut of ADT struct

// universal/randomized hashing, perfect hashing

// pagerank of ADT struct

// random projections -> <v1, v2> = 0 at high dimensions

// viterbi -> markov chain maximum likelihood estimation
