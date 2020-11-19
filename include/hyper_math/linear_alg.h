// our implementations of linear algebra structures
// NOTE: chose specifically to treat vectors and matrices as separate entities
// since we're dealing in a physics context

#pragma once
const int OUT_OF_BOUNDS = -1;
const int UNSYMMETRIC_SIZE = -2;
const int TOO_LARGE = -3;
const int MEMORY_ERROR = -4;
const int INVALID_OP = -5;

// we should not be storing anything more than this value in a vector
const int dbl_stack = 50000;
const int DEFAULT_THREADS = 16;

// vector of double-precision elements
class CVec{
private:
    size_t cur_size;
    double* vec;
    bool column_vec;
public:
    // creates a vector of size n with zeros
    CVec(int n); 
    ~CVec();

    void transpose(); //column_vec -> set to opposite
    int len() const;
    // size_t& resize(); //how to do this? Just use the below for now.
    // e.g. cvec.resize(4) -> cvec becomes length 4.
    void resize(int);

    // vector indexer. values are assignable.
    double& operator[](int i) const; //array access -> supports negative indexes
    void operator=(CVec* oth_vec); // move that vector's memory to this one
    bool operator!=(const CVec&) const;
    bool operator==(const CVec&) const; //elementwise comparison; if not the same size, return false. (throw exception instead?)
    CVec operator+(const CVec&); //elementwise addition
    CVec operator-(const CVec&); //elementwise subtraction
    CVec operator/(const CVec&); //elementwise division
    double operator*(const CVec&); //inner product
    // CMatrix operator&(const CVec&); //tensor (outer) product

    // make a deep copy of this vector to new_vec
    void copy_to(const CVec& new_vec);
};

enum matrix_mult_types{
    parallel, strassen, randomized
};

// basically 2D-array with relevant features
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
    ~CMatrix();
    
    /////////////////////
    // USEFUL OPERATIONS
    /////////////////////

    int rows() const;
    int cols() const;
    void transpose(); // note that conjugate transpose of real is just transpose
    CVec get_dimensions();
    CMatrix matrix_multiply(CMatrix m1, CMatrix m2, matrix_mult_types mult_alg); //used to choose a multiplication algorithm
    CVec hyper_sum(CMatrix&); // special operation for 'hyper sum' -> sums all columns j of m2 and puts into new vector[j]
    void replace(CVec v, double); // assign to m[i, j] a double
    // void copy_to(const CMatrix& new_matrix);

    /////////////
    // OPERATORS
    /////////////

    // double operator[](CVec v); // matrix access m[i, j] for ith row, jth column
    bool operator==(const CMatrix&);
    CMatrix operator*(const CMatrix&); // standard O(n^3) multiplication
    CMatrix operator&(const CMatrix&); // tensor product
    CVec& operator[](int i) const; // get the ith row (transposed vector)
    // void operator[](int i); // assign to ith row

    ///////////////////////////////////
    // ENHANCED MULTIPLICATION METHODS
    ///////////////////////////////////

    // p -> number of threads to use[]
    CMatrix parallel_multiply(CMatrix&, int p);
    // lower asymptotic bound multiplication (probably the slowest in practice) 
    CMatrix strassen_multiply(CMatrix&);
    // multiply the matrices in monte-carlo style
    CMatrix mc_multiply(CMatrix&);

};
