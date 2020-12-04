#include "hmath"
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

// randomized min cut of ADT struct

// universal/randomized hashing, perfect hashing

// pagerank of ADT struct

// random projections -> <v1, v2> = 0 at high dimensions

// viterbi -> markov chain maximum likelihood estimation
