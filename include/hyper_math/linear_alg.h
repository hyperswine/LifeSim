// our implementations of linear algebra structures
// NOTE: chose specifically to treat vectors and matrices as separate entities
// since we're dealing in a physics context

#pragma once
#include "hyper_math/hypmath.h"

const int OUT_OF_BOUNDS = -1;
const int UNSYMMETRIC_SIZE = -2;
const int TOO_LARGE = -3;
const int MEMORY_ERROR = -4;
const int INVALID_OP = -5;

// Arbitrary Limit: we should not be storing anything more than this value in a vector
// May have to adjust depending on practice
const int dbl_stack = 50000;
const int DEFAULT_THREADS = 16;

class CVec;
class CMatrix;

// Vector of quadruple-precision (128bit) elements
class CVec{
private:
    size_t cur_size;
    quadruple* vec;
    bool column_vec;
public:
    CVec();
    // creates a vector of size n with zeros
    CVec(int); 
    CVec(int, bool);
    // copy constructor
    CVec(const CVec&);
    ~CVec();

    quadruple* begin(){return vec;}
    quadruple* end(){return vec + cur_size;}

    void transpose(); //column_vec -> set to opposite
    int len() const;
    void resize(int);
    void print_vec();

    // vector indexer. values are assignable.
    quadruple& operator[](int i) const; //array access -> supports negative indexes
    void operator=(quadruple*); // assign to a new array. Care should be taken to ensure new malloced array is the same size.
    void operator=(CVec& oth_vec); // move that vector's memory to this one
    bool operator!=(const CVec&) const;
    bool operator==(const CVec&) const; //elementwise comparison; if not the same size, return false. (throw exception instead?)
    CVec operator+(const CVec&); //elementwise addition
    CVec operator-(const CVec&); //elementwise subtraction
    CVec operator/(const CVec&); //elementwise division
    quadruple operator*(const CVec&); //inner product
    CVec operator*(const quadruple); //elementwise multiplication
    CMatrix operator&(const CVec&); //tensor (outer) product
    quadruple operator|(const CVec&); // distance between this vector and the other one.
};

enum matrix_mult_types{
    parallel, strassen, randomized
};

// for appending matrices
enum append_direction{
    left_d, right_d, upper_d, lower_d
};

// Basically 2D-array with relevant features
class CMatrix{
private:
    int n;
    int m;
    CVec* matrix;

public:
    // Default Constructor. Recommended to use CMatrix(n, m) instead.
    // Creates a 1x1 matrix of 0
    CMatrix();
    CMatrix(int n, int m);
    CMatrix(const CMatrix&); // const reference means we cant reassign that reference to something else. But I think we can still change its internals unless we pass as a const X const.
    ~CMatrix();
    
    /////////////////////
    // USEFUL OPERATIONS
    /////////////////////

    int rows() const;
    int cols() const;
    void transpose(); // note that conjugate transpose of real is just transpose
    CVec get_dimensions();
    CVec hyper_sum(CMatrix&); // special operation for 'hyper sum' -> sums all columns j of m2 and puts into new vector[j]
    void replace(CVec v, quadruple); // assign to m[i, j] a quadruple
    void print_matrix();
    // divide matrix into quadrants
    cquad<CMatrix> div_quadrants();
    void resize(int, int);
    // return the result of appending a matrix to the current one, in 4 possible directions
    CMatrix append(CMatrix&, append_direction);

    /////////////
    // OPERATORS
    /////////////

    bool operator==(const CMatrix&);
    CMatrix operator*(const CMatrix&); // standard O(n^3) multiplication
    CMatrix operator&(const CMatrix&); // tensor product/kronecker product
    CVec& operator[](int i) const; // get the ith row (transposed vector)
    CMatrix operator-(const CMatrix&); // elementwise subtraction
    CMatrix operator+(const CMatrix&); // elementwise addition

    ///////////////////////////////////
    // ENHANCED MULTIPLICATION METHODS
    ///////////////////////////////////

    // abstraction to choose a multiplication algorithm
    CMatrix matrix_multiply(CMatrix& m2, matrix_mult_types mult_alg);
    // p -> number of threads to use[]
    CMatrix parallel_multiply(CMatrix&, int p);
    // lower asymptotic bound multiplication (probably the slowest in practice) 
    CMatrix strassen_multiply(CMatrix&);
    // multiply the matrices in monte-carlo style
    CMatrix mc_multiply(CMatrix&);

};


// A '3D' tensor. Analogous to a three-dimensional list
// We separate tensors into vectors, matrices and 3d tensors only. For our purposes, higher dimensional tensors are probably unnecessary.
// class CTensor3D{
// private:
//     CMatrix* tensor3d;

// public:
//     CTensor3D();
//     // specify length, width, depth - how many matrices
//     CTensor3D(int, int, int);
//     ~CTensor3D();

//     void print_tensor();
//     int rows();
//     int cols();
//     int depth();

//     CMatrix& operator[](int);
// };
