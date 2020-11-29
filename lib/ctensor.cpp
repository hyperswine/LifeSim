#include "hyper_math/fcomplex.h"
#include "hyper_math/ctensor.h"
#include <cmath>
#include <iostream>

#define init_vec(n) {column_vec = true; vec = new complexv[n]; cur_size = n;}

// create a length 1 column vector
cvec::cvec() {
    init_vec(1)
}
cvec::cvec(int n) {
    init_vec(n)
}
cvec::cvec(cvec& to_copy){
    init_vec(to_copy.len())

    for(int i=0; i<to_copy.len(); i++)
        vec[i] = to_copy[i];
}
cvec::~cvec() {
    delete[] vec;
}

void cvec::transpose() {
    column_vec = !column_vec;
}

int cvec::len() {
    return cur_size;
}

void cvec::print_vec() {
    if (column_vec) {
        std::cout << "==Column vector, size: " << cur_size << std::endl;
        for (int i = 0; i < cur_size; i++) {
            std::cout.precision(2);
            std::cout << std::scientific << vec[i].re() << " i*" << vec[i].im() << std::endl;
        }
    }
    else {
        std::cout << "==Row vector, size: " << cur_size << std::endl;
        for (int i = 0; i < cur_size; i++) {
            std::cout.precision(2);
            std::cout << std::scientific << " " << vec[i].re() << " i*" << vec[i].im();
        }
        std::cout << std::endl;
    }
    std::cout << "==End vector\n" << std::endl;
}

complexv cvec::operator*(const cvec& oth_vec) {
    if (cur_size != oth_vec.cur_size) throw - 1; // replace -1 with macro

    complexv res;
    for (int i = 0; i < cur_size; i++) {
        res += vec[i] * oth_vec[i];
    }

    return res;
}
// if length is odd, then returns floor(len/2) for odd and ceil(len/2) for even
// if length is even, returns len/2 for both. Thus floor(len/2) ODD, ceil(len/2) EVEN in both cases.
cvec cvec::operator[](ODD_EVEN type) {
    if(len()==1) return cvec(*this);

    if (type.even == false) {
        // take every alternating index starting from [1]
        cvec res(std::floor(len() / 2));
        for (int i = 1; i < len(); i += 2)
            res[i] = vec[i];

        return res;
    }
    else {
        // take every alternating index starting from [0]
        cvec res(std::ceil(len() / 2));

        for (int i = 0; i < len(); i += 2)
            res[i] = vec[i];

        return res;
    }
}
complexv& cvec::operator[](int& i) const {
    if (abs(i) >= cur_size) throw - 1;

    int indexer = i % cur_size;
    return vec[indexer];
}
complexv& cvec::operator[](int&& i) const {
    if (abs(i) >= cur_size) throw - 1;

    int indexer = i % cur_size;
    return vec[indexer];
}
// copy everything from oth_vec to this vec
// resize if necessary
void cvec::operator=(const cvec& oth_vec) {
    if (cur_size != oth_vec.cur_size) {
        cur_size = oth_vec.cur_size;
        delete[] vec;
        vec = new complexv[cur_size];
    }

    for (int i = 0; i < cur_size; i++) vec[i] = oth_vec[i];
}

cmatrix::cmatrix(){

}
cmatrix::cmatrix(int _rows, int _cols){

}
cmatrix::~cmatrix(){

}


int cmatrix::rows(){
    return n;
}
int cmatrix::cols(){
    return m;
}
// turn matrix from n x m to m x n
void cmatrix::transpose(){
    return;
}
void cmatrix::print_matrix(){
    return;
}

// matrix-matrix multiplication O(n^3) -> O(1) for 2x2 DFT
cmatrix cmatrix::operator*(const cmatrix& m2){
    return cmatrix();
}
// matrix-vector multiplication O(nm)
cvec cmatrix::operator*(const cvec& v2){
    return cvec(1);
}
cvec& cmatrix::operator[](int& i){
    return matrix[i];
}
cvec& cmatrix::operator[](int&& i){
    return matrix[i];
}
