#include <iostream>
#include <string.h>
#include "hyper_math/linear_alg.h"

struct xd{
    int * p;
    int gg;
    int _x;
    // assign x with '=', check if equivalent with '=='
    int& operator=(int x){
        return _x;
    }
};

int& a_lamo(int& in, struct xd* _xd){
    in = 5;
    
    return _xd->gg;
}

void t1(){
    int g = 6;
    int k = 3;
    struct xd _xd;
    _xd.gg = 10;
    _xd.p = &_xd.gg;
    a_lamo(g, &_xd) = 7;

    std::cout << "g: " << g << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "_xd.gg: " << _xd.gg << std::endl;
    std::cout << "_xd.p: " << _xd.p << std::endl;
    std::cout << "*_xd.p: " << *_xd.p << std::endl;
}

void t2(){
    CMatrix cmat(1, 1);
    CVec cvec(100);
    CVec cvec2(100);

    if (cvec == cvec2) std::cout << "Nice vector!" << std::endl;
    if (cvec[0] == cvec2[0]) std::cout << "Very nice vector!" << std::endl;
    if (cmat.rows()==1 && cmat.cols()==1) std::cout << "Nice matrix!" << std::endl;
    if (cmat[0][0] == 0) std::cout << "Very nice matrix!" << std::endl;
}

// print current matrix
// void print_cmatrix(CMatrix& m){
//     // print each row, line by line
//     std::cout<< "===Matrix:" << m.rows() << "x" << m.cols() << "====" << std::endl;
//     for(int i=0; i<m.rows(); i++){
//         for(int j=0; j<m.cols(); j++){
//             std::cout << " " << m[i][j]; 
//         }
//         // end line
//         std::cout << "\n";
//     }
//     std::cout<< "------END Matrix" << std::endl;
// }

void t3(){
    CMatrix cmat1(10, 10);
    CMatrix cmat2(10, 10);

    CMatrix res = cmat1 * cmat2;
    CMatrix res2 = cmat1 & cmat2;
    // std::cout << res[0][1] << std::endl;

    // print out res
    res2.print_matrix();
}

void t4(){
    CVec cv(10);
    CVec cv2(10);

    double* x = new double[10];
    for(int i=0; i<10; i++) x[i] = 0.5 + i;
    cv = x;

    cv.print_vec();

    cv.transpose();
    cv.print_vec();
}

int main(){
    t3();
    t4();

    return 0;
}
