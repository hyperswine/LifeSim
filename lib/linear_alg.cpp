#include "hyper_math/linear_alg.h"
#include <any>
#include <math.h>
#include <iostream>

#define zero_vec(x, n) memset(x, 0, n*sizeof (double))
#define move_x(vec1, vec2) memmove(vec2, vec1, sizeof vec2)
#define size_eq(vec1, vec2) (vec1.len() == vec2.len())

#define op_vec(operate) if(len() != oth_vec.len()) return false; CVec res(len()); for(int i=0; i<len(); i++) res[i] = vec[i] operate oth_vec[i]; return res;

CVec::CVec(){
    vec = new double[1];
    zero_vec(vec, 1);
    cur_size = 1;
    column_vec = true;
}

// create a new vector (max size = dbl_stack -> 50,000 elements)
CVec::CVec(int n){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new double[n];
    zero_vec(vec, n);

    cur_size = n;
    column_vec = true;
}

CVec::CVec(int n, bool col_vec){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new double[n];
    zero_vec(vec, n);

    cur_size = n;
    column_vec = col_vec;
}

CVec::CVec(const CVec& copy_from){
    // initialize this object as the object we want
    column_vec = copy_from.column_vec;
    cur_size  = copy_from.len();
    vec = new double[cur_size];
    
    // be sure that this works -> should work since double is primitive & only one level of pointer
    memmove(vec, copy_from.vec, cur_size*sizeof (double));
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

void CVec::print_vec(){
    if(column_vec){
        std::cout << "==Column vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++)
            std::cout << vec[i] << std::endl; 
    }
    else{
        std::cout << "==Row vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++)
            std::cout << " " << vec[i];
        std::cout << std::endl;
    }
    std::cout << "==End vector\n" << std::endl;
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
// WARNING: only works if you've dynamically allocated the new_arr and is same length
// Would be fatal if not.
void CVec::operator=(double* new_arr){
    // assign vec
    vec = new_arr;
}
void CVec::operator=(CVec& oth_vec){
    // move the memory from oth_vec to this vec
    column_vec = oth_vec.column_vec;
    cur_size  = oth_vec.len();
    vec = new double[cur_size];
    
    // be sure that this works -> should work since double is primitive & only one level of pointer
    memmove(vec, oth_vec.vec, cur_size*sizeof (double));
}
// elementwise addition
CVec CVec::operator+(const CVec& oth_vec){
    op_vec(+)
}
// elementwise subtraction
CVec CVec::operator-(const CVec& oth_vec){
    op_vec(-)
}
// elementwise division
CVec CVec::operator/(const CVec& oth_vec){
    op_vec(/)
}
// compute dot product
double CVec::operator*(const CVec& oth_vec){
    if(len() != oth_vec.len()) return false;

    double scalar_sum = 0;
    for(int i=0; i<len(); i++) scalar_sum += vec[i] * oth_vec[i];

    return 0;
}
CMatrix CVec::operator&(const CVec& oth_vec){
    CMatrix res(cur_size, oth_vec.len());
    for(int i=0; i<cur_size; i++)
        for(int j=0; j<oth_vec.len(); j++)
            res[i][j] = vec[i] * oth_vec[j];
        
    return res;
}
// distance between this vec and another vec. Works for opposite transposed vectors as well.
double CVec::operator|(const CVec& oth_vec){
    if(cur_size != oth_vec.len()) throw INVALID_OP;

    double dist = 0;
    for(int i=0; i<cur_size; i++) dist += pow((vec[i]-oth_vec[i]), 2);
    
    return sqrt(dist);
}

void CVec::resize(int new_size){
    if(new_size <= 0 || new_size > dbl_stack) throw INVALID_OP;
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

// good for testing only
CMatrix::CMatrix(){
    n = 1;
    m = 1;
    matrix = new CVec;
}

CMatrix::CMatrix(int row_len, int col_len){
    matrix = new CVec[row_len];
    for (int i=0; i<row_len; i++){
        matrix[i].resize(col_len);
        matrix->transpose(); // each CVec is a row vector
    }
    
    // perhaps we have to store pointers to these instead?
    n = row_len;
    m = col_len;
}

CMatrix::CMatrix(const CMatrix& copy_from){
    n = copy_from.rows();
    m = copy_from.cols();
    // copy the matrix row by row with CVec copy constructor
    matrix = new CVec[n];

    for(int i=0; i<n; i++){
        matrix[i] = CVec(copy_from.matrix[i]);
    }
}

CMatrix::~CMatrix(){
    // NOTE: may have to use for loop delete instead
    delete[] matrix;
}

// print current matrix
void CMatrix::print_matrix(){
    // print each row, line by line
    std::cout<< "===Matrix:" << rows() << "x" << cols() << "====" << std::endl;
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            std::cout << " " << matrix[i][j]; 
        }
        // end line
        std::cout << "\n";
    }
    std::cout<< "===END Matrix\n" << std::endl;
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
    CMatrix temp(*this); // temp should be auto deleted as we exit this function
    
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            matrix[i][j] = temp[j][i];
        }
    }
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
CMatrix CMatrix::operator&(const CMatrix& m2){
    CMatrix res(rows()*m2.rows(), cols()*m2.cols());
    // multiply two matrices (n x m) & (p x q) so that we end up with (np x mq)
    // O(nmpq) space complexity -> O(n^4) time worst case square matrices of same size
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            // p starts from i*m2.rows...i*m2.rows+m2.rows
            for(int p=i*m2.rows(); p<i*m2.rows()+m2.rows(); p++){
                // q starts from j*m2.cols...j*m2.cols+m2.cols
                for(int q=j*m2.cols(); q<j*m2.cols()+m2.cols(); q++){
                    // compute the element a_ij * b_ij
                    double elem = matrix[i][j] * m2[i][j];
                    // assign to p, q
                    res[p][q] = elem;
                }
            }
        }
    }

    return res;
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

// don't have to worry about indexing m, since handled by cvec
CVec& CMatrix::operator[](int i) const{
    if(abs(i) >= n) throw OUT_OF_BOUNDS;

    int indexer = i % n;
    return matrix[indexer];
}

CMatrix CMatrix::matrix_multiply(const CMatrix& m2, matrix_mult_types mult_alg){
    // ensure that m1 and m2 are the right dimensions
    if (cols() != m2.rows()) throw UNSYMMETRIC_SIZE;    

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
        return *this * m2;
    }

}

// MULTIPLICATION ALGORITHMS

CMatrix CMatrix::parallel_multiply(const CMatrix& m2, int p){
    CMatrix res(cols(), m2.rows());
    // set threads = p

    // parallel for loop/div and conquer (not strassen)

    return res;
}

CMatrix CMatrix::strassen_multiply(const CMatrix& m2){
    CMatrix res(cols(), m2.rows());

    // divide and conquer

    return res;
}

CMatrix CMatrix::mc_multiply(const CMatrix& m2){
    CMatrix res(cols(), m2.rows());

    // randomized

    return res;
}
