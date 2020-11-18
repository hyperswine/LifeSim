// our implementations of linear algebra structures
// NOTE: chose specifically to treat vectors and matrices as separate entities
// since we're dealing in a physics context

#pragma once
const int OUT_OF_BOUNDS = -1;
const int UNSYMMETRIC_SIZE = -2;
const int TOO_LARGE = -3;
const int MEMORY_ERROR = -4;

// we should not be storing anything more than this value in a vector
const int dbl_stack = 50000;
const int DEFAULT_THREADS = 16;

// vector of double-precision elements
class CVec{
private:
    size_t cur_size;
    double* vec;
public:
    CVec(int n);
    ~CVec();

    void transpose();
    int len();

    double operator[](int i); //array access -> supports negative indexes
    CVec operator+(const CVec&); //elementwise addition
    CVec operator-(const CVec&); //elementwise subtraction
    double operator*(const CVec&); //inner product
    CVec operator&(const CVec&); //tensor (outer) product
};

enum matrix_mult_types{
    parallel, strassen, randomized
};

// basically 2D-array with relevant features
class Matrix{
private:
    int n;
    int m;
    // alternative implementation -> use cvecs?
    double** matrix;

public:
    Matrix(int n, int m);
    ~Matrix();
    int rows() const;
    int cols() const;

    void transpose(); // note that conjugate transpose of real is just transpose
    CVec get_dimensions();

    Matrix matrix_multiply(Matrix m1, Matrix m2, matrix_mult_types mult_alg); //used to choose a multiplication algorithm
    double hyper_sum(Matrix&); // special operation for 'hyper sum' -> sums all columns j of m2 and puts into new vector[j]
    Matrix operator&(const Matrix&);
    double operator[](CVec v); // matrix access m[i, j] for ith row, jth column
    void replace(CVec v, double); // assign to m[i, j] a double
    CVec operator[](int i) const; // get the ith row (transposed vector)
    // void operator[](int i); // assign to ith row

    // NOTE: use * operator for the standard algorithm of multiplication
    Matrix operator*(const Matrix&);
    // p -> number of threads to use[]
    Matrix parallel_multiply(Matrix&, int p);
    // lower asymptotic bound multiplication (probably the slowest in practice) 
    Matrix strassen_multiply(Matrix&);
    // multiply the matrices in monte-carlo style
    Matrix mc_multiply(Matrix&);

};


