#include "hmath"
#include "mc_methods.h"

#include <utility>
#include <vector>
#include <string>

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

// Find the next prime >= num.
// If num is prime, then returns num.
static int find_next_prime(int num){
    // assume that a negative number was a mistake
    if(num < 0) num = -num;
    if(num <= 2) return 3; // not the worst idea

    int l = num;
    bool flag = false;
    while(flag == false){
        flag = true;
        for(int i=2; i<ceil(sqrt(l)); i++){
            if(l%i == 0){
                flag = false;
                l++;
                break;
            }
        }        
    }

    return l;
}

const int ascii_size = 256;

// universal/randomized hashing, perfect hashing
// each key must differ in at least one location
void perfect_hash(std::vector<std::string> x){
    int M = ascii_size;

    // take the max length of the strings = k
    int k = 0;
    for(int i=0; i<x.size(); i++){
        if(x[i].length() > k) k = x[i].length();
    }

    // represent each key x as a vector of integers, where each integer <= M-1
    std::vector<std::vector<int>> x_s;
    for(int i=0; i<x.size(); i++){
        for(int j=0; j<x[i].length(); i++){
            x_s[i][j] = atoi(x[i][j]);
        }
    }

    // generate a random r vector of length k, where each integer in [0, M-1]
    std::vector<int> r;
    RAND_ENG::RNG rng;
    for(int i=0; i<k; i++){
        r.push_back(rng.gen_int(0, M-1));
    }
    
    // find some prime p, where p >= M
    int p = find_next_prime(M);

    // for all keys x
    //  compute the hash index h(x) = r_1*x_1 + r_2*x_2 + ... + r_k*x_k (mod M)
    std::vector<int> hash_indexes;
    for(int i=0; i<x.size(); i++){
        int res = (r * x_s[i]) % p;
        hash_indexes.push_back(res);
    }
    
    // evaulate the indexes assigned to all keys
    // if there exists a conflict on a certain index i, hash again using the previous algorithm with random r vectors again
    for(int i=0; i<p; i++){
        int n_hits = 0;
        for (int j = 0; j <hash_indexes.size(); j++){

        }
        // if n hits > 1, then conflict on index i and thus make a second level hash table.
    }
}

// randomized min cut of ADT struct


// pagerank of ADT struct

// random projections -> <v1, v2> = 0 at high dimensions

// viterbi -> markov chain maximum likelihood estimation
