#include "hyper_math/qtensor.h"
#include "hyper_math/hypmath.h"
#include "backend.h"
#include <string>
#include <any>
#include <cmath>
#include <iostream>

#define zero_vec(x, n) memset(x, 0, n*sizeof (quadruple))
#define move_x(vec1, vec2) memmove(vec2, vec1, sizeof vec2)
#define size_eq(vec1, vec2) (vec1.len() == vec2.len())
#define max_dimension(a, b) (a > b)? a: b
#define max2_dimension(a, b, c, d) max_dimension(a, b) > max_dimension(c, d) ? max_dimension(a, b) : max_dimension(c, d)

#define op_vec(operate) if(len() != oth_vec.len()) return false; qvec res(len()); for(int i=0; i<len(); i++) res[i] = vec[i] operate oth_vec[i]; return res;

qvec::qvec(){
    vec = new quadruple[1];
    zero_vec(vec, 1);
    cur_size = 1;
    column_vec = true;
}

// create a new vector (max size = dbl_stack -> 50,000 elements)
qvec::qvec(int n){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new quadruple[n];
    zero_vec(vec, n);

    cur_size = n;
    column_vec = true;
}

qvec::qvec(int n, bool col_vec){
    if (n > dbl_stack) throw TOO_LARGE;
    vec = new quadruple[n];
    zero_vec(vec, n);

    cur_size = n;
    column_vec = col_vec;
}

qvec::qvec(const qvec& copy_from){
    // initialize this object as the object we want
    column_vec = copy_from.column_vec;
    cur_size  = copy_from.len();
    vec = new quadruple[cur_size];
    
    // be sure that this works -> should work since quadruple is primitive & only one level of pointer
    memmove(vec, copy_from.vec, cur_size*sizeof (quadruple));
}

qvec::~qvec(){
    if(vec) delete[] vec;
}

int qvec::len() const{
    return cur_size;
}

void qvec::transpose(){
    column_vec = !column_vec;
}

void qvec::print_vec(){
    if(column_vec){
        std::cout << "==Column vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++){
            std::cout.precision(2); 
            std::cout << std::scientific << vec[i] << std::endl;
        }
    }
    else{
        std::cout << "==Row vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++){
            std::cout.precision(2); 
            std::cout << std::scientific << " " << vec[i];
        }
        std::cout << std::endl;
    }
    std::cout << "==End vector\n" << std::endl;
}
qvec qvec::operator[](odd_even type){
    if(type == ODD_T){
        qvec res(std::floor(len()/2));
        for(int i=1; i<len(); i+=2)
            res[i] = vec[i];

        return res;
    }
    else{
        qvec res(std::ceil(len()/2));

        for(int i=0; i<len(); i+=2)
            res[i] = vec[i];

        return res;
    }
}
quadruple& qvec::operator[](int& i) const{
    if(abs(i) >= cur_size) throw OUT_OF_BOUNDS;

    size_t indexer = i % cur_size;
    return vec[indexer];
}
// assume that an index > size is a mistake. A negative index < -size = backward indexing.
quadruple& qvec::operator[](int&& i) const{
    // out of bounds vector access
    if(abs(i) >= cur_size) throw OUT_OF_BOUNDS;

    size_t indexer = i % cur_size; // for negative indexing
    return vec[indexer];
}
bool qvec::operator!=(const qvec& oth_vec) const{
    return !(*this==oth_vec);
}
bool qvec::operator==(const qvec& oth_vec) const{
    if(cur_size != oth_vec.len()) return false;

    for(int i=0; i<cur_size; i++) if(vec[i] != oth_vec[i]) return false;

    return true;
}
// WARNING: only works if you've dynamically allocated the new_arr and is same length
// Would be fatal if not.
void qvec::operator=(quadruple* new_arr){
    // assign vec
    delete[] vec;
    vec = new_arr;
}
void qvec::operator=(qvec& oth_vec){
    // move the memory from oth_vec to this vec
    column_vec = oth_vec.column_vec;
    cur_size  = oth_vec.len();
    delete[] vec;
    vec = new quadruple[cur_size];
    
    // be sure that this works -> should work since quadruple is primitive & only one level of pointer
    // basically overwrites everything in this
    memmove(vec, oth_vec.vec, cur_size*sizeof (quadruple));
}
// elementwise addition
qvec qvec::operator+(const qvec& oth_vec){
    op_vec(+)
}
// elementwise subtraction
qvec qvec::operator-(const qvec& oth_vec){
    op_vec(-)
}
// elementwise division
qvec qvec::operator/(const qvec& oth_vec){
    op_vec(/)
}
// compute dot product
quadruple qvec::operator*(const qvec& oth_vec){
    if(len() != oth_vec.len()) return false;

    quadruple scalar_sum = 0;
    for(int i=0; i<len(); i++) scalar_sum += vec[i] * oth_vec[i];

    return scalar_sum;
}
// elementwise multiplication
qvec qvec::operator*(const quadruple m){
    qvec res(cur_size);
    for(int i=0; i<cur_size; i++) res[i] *= m;
    return res;
}
qmatrix qvec::operator&(const qvec& oth_vec){
    qmatrix res(cur_size, oth_vec.len());
    for(int i=0; i<cur_size; i++)
        for(int j=0; j<oth_vec.len(); j++)
            res[i][j] = vec[i] * oth_vec[j];
        
    return res;
}
// distance between this vec and another vec. Works for opposite transposed vectors as well.
quadruple qvec::operator|(const qvec& oth_vec){
    if(cur_size != oth_vec.len()) throw INVALID_OP;

    quadruple dist = 0;
    for(int i=0; i<cur_size; i++) dist += pow((vec[i]-oth_vec[i]), 2);
    
    return sqrt(dist);
}

void qvec::resize(int new_size){
    if(new_size <= 0 || new_size > dbl_stack) throw INVALID_OP;
    quadruple* new_vec = new quadruple[new_size];

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
qmatrix::qmatrix(){
    n = 1;
    m = 1;
    matrix = new qvec;
}

qmatrix::qmatrix(int row_len, int col_len){
    matrix = new qvec[row_len];
    for (int i=0; i<row_len; i++){
        matrix[i].resize(col_len);
        matrix->transpose(); // each qvec is a row vector
    }
    
    // perhaps we have to store pointers to these instead?
    n = row_len;
    m = col_len;
}

qmatrix::qmatrix(const qmatrix& copy_from){
    n = copy_from.rows();
    m = copy_from.cols();
    // copy the matrix row by row with qvec copy constructor
    matrix = new qvec[n];

    for(int i=0; i<n; i++){
        matrix[i] = qvec(copy_from.matrix[i]);
    }
}

qmatrix::~qmatrix(){
    // NOTE: may have to use for loop delete instead
    delete[] matrix;
}

// print current matrix
// NOTE: need to space the numbers according to the largest number of significant digits
void qmatrix::print_matrix(){
    // print each row, line by line
    std::cout<< "===Matrix:" << rows() << "x" << cols() << "====" << std::endl;
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            std::cout.precision(2);
            std::cout << std::scientific << " " << matrix[i][j]; 
        }
        // end line
        std::cout << "\n";
    }
    std::cout<< "===END Matrix\n" << std::endl;
}

int qmatrix::rows() const{
    return n;
}

int qmatrix::cols() const{
    return m;
}

qvec qmatrix::get_dimensions(){
    qvec dimensions(2);
    dimensions[0] = rows();
    dimensions[1] = cols();

    return dimensions;
}

void qmatrix::transpose(){
    // simply reverse rows and cols [i, j] -> [j, i]
    qmatrix temp(*this); // temp should be auto deleted as we exit this function
    
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            matrix[i][j] = temp[j][i];
        }
    }
}

void qmatrix::resize(int a, int b){
    if(a == rows() && b == cols()) return;

    // make res, then remake matrix & copy res
    qmatrix res(a, b);

    // only have to care about enlargening, shrinking done automatically
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            // default
            if(i < rows() && j < cols())
                res[i][j] = matrix[i][j];
            // enlargening: technically dont need else if, but just in case
            else if(i >= rows() || j >= cols())
                res[i][j] = 0;
        }
    }
    delete[] matrix;
    matrix = new qvec[a];
    n = a;
    m = b;

    // initialize matrix
    for (int i=0; i<a; i++){
        matrix[i].resize(b);
        matrix->transpose(); // each qvec is a row vector
    }

    // apply copy constructor on all qvecs
    for(int i=0; i<a; i++) matrix[i] = res[i];
}

// if matrix isn't square, there will be problems
// NOTE: HAVE TO DO THIS THE HARD WAY IT SEEMS
// UNLESS YOU CAN FIGURE OUT HOW TO DO THOSE INDEXES PROPERLY
cquad<qmatrix> qmatrix::div_quadrants(){
    if(rows() != cols() || rows() == 1 || cols() == 1) throw INVALID_OP;

    // floor(row/2) - 1 and floor(row/2) for indicies
    // e.g. 5 x 5 matrix -> upperleft = f1 x f1, upperright = f1 x f2
    //                      lowerleft = f2 x f1, lowerright f2 x f2
    int f1 = rows() / 2;
    int f2 = rows() / 2;
    c_log(std::to_string(f1) + std::to_string(f2));

    qmatrix cm1(f1,f1);
    qmatrix cm2(f1,f2+1);
    qmatrix cm3(f2+1,f1);
    qmatrix cm4(f2+1,f2+1);
    // divide matrix into 4 chunks and return them

    // copy upperleft
    for(int i=0; i<f1; i++)
        for(int j=0; j<f1; j++)
            cm1[i][j] = matrix[i][j];
        
    // copy upperright
    for(int i=0; i<f1; i++)
        for(int j=f1; j<cols(); j++)
            cm2[i][j] = matrix[i][j];
 
    // copy lowerleft
    for(int i=f1; i<rows(); i++)
        for(int j=0; j<f1; j++)
            cm3[i][j] = matrix[i][j];

    // copy lowerright
    for(int i=f1; i<rows(); i++)
        for(int j=f1; j<cols(); j++)
            cm4[i][j] = matrix[i][j];
    
    cquad<qmatrix> res(cm1, cm2, cm3, cm4);
    return res;
}

// append m2 to m1 from a direction
// NOTE: m1 & m2 must have the same side equal for which you want to append to
// m1 & m2 can have different adjacent sides.
qmatrix qmatrix::append(qmatrix& m2, append_direction direction){

    switch (direction){
    case right_d:{
        if(rows() != m2.rows()) throw INVALID_OP;
        qmatrix res(rows(), cols() + m2.cols());
        // copy m1 on the left
        for(int i=0; i<rows(); i++){
            for(int j=0; j<cols(); j++){
                res[i][j] = matrix[i][j];
            }
        }
        // copy m2 on the right
        // e.g. 10x10 -right-> 10x20 = 10x30
        // 0..rows(), cols()..m2.cols() -translate-> 0..m2.cols()
        for(int i=0; i<rows(); i++){
            for(int j=cols(); j<cols() + m2.cols(); j++){
                res[i][j] = m2[i][cols() - j];
            }
        }
        return res;
        break;
    }

    case left_d:{
        if(rows() != m2.rows()) throw INVALID_OP;

        qmatrix res(rows(), cols() + m2.cols());
        // copy m2 on the left
        for(int i=0; i<rows(); i++){
            for(int j=0; j<m2.cols(); j++){
                res[i][j] = m2[i][j];
            }
        }
        // copy m1 on the right
        for(int i=0; i<rows(); i++){
            for(int j=m2.cols(); j<cols() + m2.cols(); j++){
                res[i][j] = matrix[i][j];
            }
        }
        return res;
        break;
    }

    case lower_d:{
        if(cols() != m2.cols()) throw INVALID_OP;

        qmatrix res(rows() + m2.rows(), cols());
        // copy m1 on the upper
        for(int i=0; i<rows(); i++){
            for(int j=0; j<cols(); j++){
                res[i][j] = matrix[i][j];
            }
        }
        // copy m2 on the lower
        for(int i=rows(); i<rows() + m2.rows(); i++){
            for(int j=0; j<cols(); j++){
                res[i][j] = m2[i][j];
            }
        }
        return res;
        break;
    } 

    case upper_d:{
        if(cols() != m2.cols()) throw INVALID_OP;

        qmatrix res(rows() + m2.rows(), cols());
        // copy m1 on the lower
        for(int i=m2.rows(); i<rows() + m2.rows(); i++){
            for(int j=0; j<cols(); j++){
                res[i][j] = matrix[i][j];
            }
        }
        // copy m2 on the upper
        for(int i=0; i<m2.rows(); i++){
            for(int j=0; j<cols(); j++){
                res[i][j] = m2[i][j];
            }
        }
        return res;
        break;
    }

    default:
        break;
    }

    // this shouldn't happen
    return qmatrix();
}

qvec& qmatrix::operator[](int& i) const{
    if(abs(i) >= n) throw OUT_OF_BOUNDS;

    int indexer = i % n;
    return matrix[indexer];
}
qvec qmatrix::operator*(const qvec& vec_mult){
    if(vec_mult.len() != cols()) throw INVALID_OP;

    qvec res(rows());
    // multiply each cvec 
    for(int i=0; i<rows(); i++){
        res[i] = matrix[i] * vec_mult;
    }

    return res;
}
qmatrix qmatrix::operator*(const qmatrix& m2){
    if (cols() != m2.rows()) throw UNSYMMETRIC_SIZE;

    qmatrix res_matrix(rows(), m2.cols());
    for(int i = 0; i<rows(); i++)
        for(int j = 0; j<m2.cols(); j++)
            for(int k = 0; k<cols(); k++)
                res_matrix[i][j] += matrix[i][k] * m2[k][j];
        
    return res_matrix;
}
qmatrix qmatrix::operator&(const qmatrix& m2){
    qmatrix res(rows()*m2.rows(), cols()*m2.cols());
    // multiply two matrices (n x m) & (p x q) so that we end up with (np x mq)
    // O(nmpq) space complexity -> O(n^4) time worst case square matrices of same size
    for(int i=0; i<rows(); i++){
        for(int j=0; j<cols(); j++){
            // p starts from i*m2.rows...i*m2.rows+m2.rows
            for(int p=i*m2.rows(); p<i*m2.rows()+m2.rows(); p++){
                // q starts from j*m2.cols...j*m2.cols+m2.cols
                for(int q=j*m2.cols(); q<j*m2.cols()+m2.cols(); q++){
                    // compute the element a_ij * b_ij
                    quadruple elem = matrix[i][j] * m2[i][j];
                    // assign to p, q
                    res[p][q] = elem;
                }
            }
        }
    }

    return res;
}
bool qmatrix::operator==(const qmatrix& m2){
    if(rows() != m2.rows() && cols() != m2.cols()) return false;
    // compare elementwise
    for(int r = 0; r < rows(); r++){
        for(int c = 0; c < cols(); c++){
            if(matrix[r][c] != m2[r][c]) return false;
        }
    }

    return true;
}
// don't have to worry about indexing m, since handled by qvec
qvec& qmatrix::operator[](int&& i) const{
    if(abs(i) >= n) throw OUT_OF_BOUNDS;

    int indexer = i % n;
    return matrix[indexer];
}
qmatrix qmatrix::operator-(const qmatrix& m2){
    if(rows() != m2.rows() && cols() != m2.cols()) throw INVALID_OP;

    qmatrix res(rows(), cols());

    for(int i=0; i<rows(); i++)
        for(int j=0; j<cols(); j++)
            res[i][j] = matrix[i][j] - m2[i][j];

    return res;
}
qmatrix qmatrix::operator+(const qmatrix& m2){
    if(rows() != m2.rows() && cols() != m2.cols()) throw INVALID_OP;

    qmatrix res(rows(), cols());

    for(int i=0; i<rows(); i++)
        for(int j=0; j<cols(); j++)
            res[i][j] = matrix[i][j] + m2[i][j];
        
    return res;
}

qmatrix qmatrix::matrix_multiply(qmatrix& m2, matrix_mult_types mult_alg){
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

qmatrix qmatrix::parallel_multiply(qmatrix& m2, int p){
    qmatrix res(cols(), m2.rows());
    // set threads = p

    // parallel for loop/div and conquer (not strassen)

    return res;
}

/**
 * Multiply two n x n matrices together
 * NOTE: If attempting to multiply non square matrices, 0's will be auto appended to them,
 * and a warning message will be displayed
 */ 
qmatrix qmatrix::strassen_multiply(qmatrix& m2){
    // if matrices aren't both square and the same size
    if(rows() != m2.rows() || cols() != m2.cols() || rows() != cols() || m2.rows() != m2.cols()){
        std::cout << "Warning: multiplying non square matrices" << std::endl;
        // resize matrix(s) to max_dim
        int max_a = max_dimension(rows(), cols());
        int max_b = max_dimension(m2.rows(), m2.cols());
        int max_dim = max_dimension(max_a, max_b);
        this->resize(max_dim, max_dim);
        m2.resize(max_dim, max_dim);
    }

    // O(1) op, despite naive using naive matrix mult in base case
    if(m2.rows()==1) return *this * m2;

    // split m1 & m2 into 2 quarters
    cquad<qmatrix> res1 = div_quadrants();
    cquad<qmatrix> res2 = m2.div_quadrants();

    // divide and conquer, 7 times.
    // Note the 7 operations instead of 8 is what gives this algorithm its asymptotic bound
    qmatrix r1 = res1[0].strassen_multiply(res2[1] - res2[2]);
    qmatrix r2 = (res1[0] + res1[1]).strassen_multiply(res2[3]);
    qmatrix r3 = (res1[2] + res1[3]).strassen_multiply(res2[0]);
    qmatrix r4 = res1[3].strassen_multiply(res2[0] - res2[2]);
    qmatrix r5 = (res1[0] + res1[3]).strassen_multiply(res2[0] + res2[3]);
    qmatrix r6 = (res1[1] - res1[3]).strassen_multiply(res2[1] + res2[3]);
    qmatrix r7 = (res1[0] - res1[2]).strassen_multiply(res2[0] + res2[1]);

    qmatrix upper_left = r5 + r4 - r2 + r6;
    qmatrix upper_right = r1 + r2;
    qmatrix lower_left = r3 + r4;
    qmatrix lower_right = r1 + r5 - r3 - r7;

    // append matrices and return result
    // NOTE: these appends can take up O(n^2). Simply 'adding' the two matrices together requires copying every element
    // in most implementations, so in practice strassen algorithm is very flashy but not stack-friendly.
    qmatrix upper = upper_left.append(upper_right, right_d);
    qmatrix lower = lower_left.append(lower_right, right_d);

    return upper.append(lower, lower_d);
}

qmatrix qmatrix::mc_multiply(qmatrix& m2){
    qmatrix res(cols(), m2.rows());

    // randomized

    return res;
}
