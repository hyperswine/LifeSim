#include "hyper_math/linear_alg.h"
#include <any>
#include <math.h>

#define zero_vec(x, n) memset(x, 0, n*sizeof (double))
// move_vec doesnt delete any memory, just copies it
#define move_vec(vec1, vec2) memmove(vec2, vec1, sizeof vec2)

// create a new vector (max size = dbl_stack -> 50,000 elements)
CVec::CVec(int n){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new double[n];
    zero_vec(vec, n);

    cur_size = n;
    column_vec = true;
}

CVec::~CVec(){
    if(vec) delete[] vec;
}

int CVec::len() const{
    return cur_size;
}

void CVec::transpose(){
    column_vec = !column_vec;
}

// assume that an index > size is a mistake. A negative index < -size = backward indexing.
double& CVec::operator[](int i) const{
    // out of bounds vector access
    if(abs(i) >= len()) throw OUT_OF_BOUNDS;

    size_t indexer = i % len(); // for negative indexing
    return vec[indexer];
}
bool CVec::operator!=(const CVec& oth_vec) const{
    return !(*this==oth_vec);
}
bool CVec::operator==(const CVec& oth_vec) const{
    if(len() != oth_vec.len()) return false;

    for(int i=0; i<len(); i++) if(vec[i] != oth_vec[i]) return false;

    return true;
}
void CVec::operator=(CVec* oth_vec){
    move_vec(this, oth_vec);
}
CVec CVec::operator+(const CVec& oth_vec){

    return CVec(1);
}
CVec CVec::operator-(const CVec& oth_vec){

    return CVec(1);
}
CVec CVec::operator/(const CVec& oth_vec){

    return CVec(1);
}
double CVec::operator*(const CVec& oth_vec){

    return 0;
}

void CVec::resize(int new_size){
    if(new_size <= 0) throw INVALID_OP;
    double* new_vec = new double[new_size];

    // if new len > cur_size, append zeros (memset new_len-cur_size)
    if(new_size > cur_size){
        zero_vec(new_vec, new_size);
        // copy over elements
        for(int i=0; i<cur_size; i++) new_vec[i] = vec[i];
    }
    // else the new size is smaller than the current, then truncate, and simply set new size
    else{
        for(int i=0; i<new_size; i++) new_vec[i] = vec[i];
    }
    
    cur_size = new_size;
    delete[] vec;
    vec = new_vec;
}

// shouldn't use --> good for testing only
CMatrix::CMatrix(){
    n = 1;
    m = 1;
    matrix = (CVec*)malloc(sizeof (CVec*));
    matrix[0] = CVec(1);
}

CMatrix::CMatrix(int row_len, int col_len){
    matrix = (CVec*)malloc(n * sizeof (CVec*));
    for(int i = 0; i<row_len; i++){
        // TEST: does this work?
        // I think we should be allocating dynamically
        matrix[i] = CVec(col_len);
    }
    /**
     * If doesnt work, use:
     * matrix = new CVec[n];
     * for (i=0..n) matrix[i].resize(m);
     */

    n = row_len;
    m = col_len;
}

CMatrix::~CMatrix(){
    for(int i = 0; i<n; i++){
        // delete contiguous memory
        delete[] matrix;
    }
}

int CMatrix::rows() const{
    return n;
}

int CMatrix::cols() const{
    return m;
}

CVec CMatrix::get_dimensions(){
    CVec dimensions(2);
    dimensions[0] = rows();
    dimensions[1] = cols();

    return dimensions;
}

void CMatrix::transpose(){
    // simply reverse rows and cols [i, j] -> [j, i]
}

CMatrix CMatrix::operator*(const CMatrix& m2){
    if (cols() != m2.rows()) throw UNSYMMETRIC_SIZE;

    CMatrix res_matrix(rows(), m2.cols());
    for(int i = 0; i<rows(); i++)
        for(int j = 0; j<m2.cols(); j++)
            for(int k = 0; k<cols(); k++)
                res_matrix[i][j] += matrix[i][k] * m2[k][j];
        
    return res_matrix;
}
bool CMatrix::operator==(const CMatrix& m2){
    if(rows() != m2.rows() && cols() != m2.cols()) return false;
    // compare elementwise
    for(int r = 0; r < rows(); r++){
        for(int c = 0; c < cols(); c++){
            if(matrix[r][c] != m2[r][c]) return false;
        }
    }

    return true;
}
CMatrix CMatrix::operator&(const CMatrix& m2){
    CMatrix res(rows()*m2.rows(), cols()*m2.cols());
    // multiply two matrices (n x m) & (p x q) so that we end up with (np x mq)

    // multiply row-wise

    return res;
}
CVec& CMatrix::operator[](int i) const{
    if(i < 0) throw OUT_OF_BOUNDS;
    return matrix[i];
}

CMatrix CMatrix::matrix_multiply(CMatrix m1, CMatrix m2, matrix_mult_types mult_alg){
    // ensure that m1 and m2 are the right dimensions
    CVec d1 = m1.get_dimensions();
    CVec d2 = m2.get_dimensions();
    if (d1[1] != d2[0]) throw UNSYMMETRIC_SIZE;    

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

// MULTIPLICATION ALGORITHMS

CMatrix CMatrix::parallel_multiply(CMatrix& m2, int p){
    CMatrix res(cols(), m2.rows());
    // set threads = p

    // parallel for loop/div and conquer (not strassen)

    return res;
}

CMatrix CMatrix::strassen_multiply(CMatrix& m2){
    CMatrix res(cols(), m2.rows());

    // divide and conquer

    return res;
}

CMatrix CMatrix::mc_multiply(CMatrix& m2){
    CMatrix res(cols(), m2.rows());

    // randomized

    return res;
}
