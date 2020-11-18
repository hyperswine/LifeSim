#include "hyper_math/linear_alg.h"
#include <any>
#include <math.h>

// create a new vector (max size = dbl_stack -> 50,000 elements)
CVec::CVec(int n){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new double[n];
}

CVec::~CVec(){
    if(vec) delete[] vec;
}

// assume that an index > size is a mistake. A negative index < -size is treated
// as backward indexing.
double CVec::operator[](int i){
    // out of bounds vector access
    if(abs(i) >= len()) throw OUT_OF_BOUNDS;

    size_t indexer = i % len();
    return vec[indexer];
}

Matrix::Matrix(int n, int m){
    for(int i = 0; i<n; i++){
        matrix[i] = new double[m];
    }
}

Matrix::~Matrix(){
    for(int i = 0; i<n; i++){
        // delete contiguous memory
        delete[] matrix[i];
    }
}

Matrix Matrix::operator*(const Matrix& m2){
    if (cols() != m2.rows()) throw UNSYMMETRIC_SIZE;

    Matrix res_matrix(rows(), m2.cols());
    for(int i = 0; i<m2.rows(); i++)
        for(int j = 0; j<m2.rows(); j++){

        }
    
    return res_matrix;
}

Matrix Matrix::matrix_multiply(Matrix m1, Matrix m2, matrix_mult_types mult_alg){
    // ensure that m1 and m2 are the right dimensions
    CVec d1 = m1.get_dimensions();
    CVec d2 = m2.get_dimensions();
    if (d1[1] != d2[0]) throw UNSYMMETRIC_SIZE;
    
    // create new matrix of d1[0] x d2[1]
    Matrix* res = new Matrix(d1[0], d1[1]);

    // choose a multiplication method
    if (mult_alg == strassen){
        return strassen_multiply(m2);
    }
    else if (mult_alg == randomized){
        return mc_multiply(m2);
    }
    else if (mult_alg == parallel){
        return parallel_multiply(m2, DEFAULT_THREADS);
    }
    else{
        return m1 * m2;
    }

}
