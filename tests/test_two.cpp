#include <iostream>
#include <string>
#include <random>
#include "hyper_math/qtensor.h"
#include "hyper_math/rng_engine.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/fcomplex.h"

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
    qmatrix cmat(1, 1);
    qvec qvec1(100);
    qvec qvec2(100);

    if (qvec1 == qvec2) std::cout << "Nice vector!" << std::endl;
    if (qvec1[0] == qvec2[0]) std::cout << "Very nice vector!" << std::endl;
    if (cmat.rows()==1 && cmat.cols()==1) std::cout << "Nice matrix!" << std::endl;
    if (cmat[0][0] == 0) std::cout << "Very nice matrix!" << std::endl;
}

void t3(){
    qmatrix cmat1(10, 10);
    qmatrix cmat2(10, 10);

    qmatrix res = cmat1 * cmat2;
    qmatrix res2 = cmat1 & cmat2;
    // std::cout << res[0][1] << std::endl;

    // print out res
    res2.print_matrix();
}

void t4(){
    qvec cv(10);
    qvec cv2(10);

    quadruple* x = new quadruple[10];
    for(int i=0; i<10; i++) x[i] = 0.5 + i;
    cv = x;

    cv.print_vec();

    cv.transpose();
    cv.print_vec();
}

void f1(RAND_ENG::RNG& rng){
    int x = rng.gen_int();
    std::cout << "f1() -> number generated: " << x << std::endl;
}

void t5(){
    using namespace RAND_ENG;
    RNG rng_d;
    quadruple x = rng_d.gen_quad(10, 20);
    int y = rng_d.gen_int(10, 20);

    std::cout << "main() -> double generated: " << x << std::endl;
    std::cout << "main() -> int generated: " << y << std::endl;
}

void t6(){
    RAND_ENG::RNG rng;

    qvec cv1 = rng.gen_randvec(10);
    qvec cv2 = rng.gen_randvec(10);

    // double res = cv1 * cv2;
    // std::cout << "cv1 * cv2 = " << res << std::endl;

    qvec cv3 = cv1 + cv2;
    std::cout << "cv1 + cv2 = " << std::endl;
    cv3.print_vec();

    qvec cv4 = cv1 - cv2;
    std::cout << "cv1 - cv2 = " << std::endl;
    cv4.print_vec();

    qvec cv5 = cv1 / cv2;
    std::cout << "cv1 / cv2 = " << std::endl;
    cv5.print_vec();

    qvec cv6 = cv5; // deep copy cv5 into cv6
    std::cout << "cv6 = cv5" << std::endl;
    cv6.print_vec();

    // generate random matrices
    
    qmatrix cm_rand = rng.gen_randmatrix(5, 10);
    cm_rand.print_matrix();
    qmatrix cm_rand2 = rng.gen_randmatrix(10, 5);
    cm_rand.print_matrix();

    // multiply matrices
    qmatrix cm_rand3 = cm_rand * cm_rand2;
    cm_rand3.print_matrix();

    qmatrix cm_rand5 = rng.gen_randmatrix(4, 9);
    cm_rand.print_matrix();
    qmatrix cm_rand6 = rng.gen_randmatrix(10, 5);
    cm_rand.print_matrix();

    try
    {
        cm_rand5 * cm_rand6;
    }
    catch(int x)
    {
        std::cerr << "caught! exception code: " << x << '\n';
    }
}

void t7(){
    RAND_ENG::RNG rng;
    qvec cv1 = rng.gen_randvec(10);
    qvec cv2 = rng.gen_randvec(10);
    cv1.print_vec();
    cv2.print_vec();
    
    qvec cv3 = cv1 + cv2;
    cv3.print_vec();

    cv3.transpose();
    cv3.print_vec();

    cpair<qvec> res(cv1, cv2);

    res[0].print_vec();
    res[1].print_vec();
    qmatrix cm1 = rng.gen_randmatrix(10, 10);
    cm1.print_matrix();
    cm1.resize(5,30);
    cm1.print_matrix();
    cm1.resize(15, 20);
    cm1.print_matrix();
    cm1.resize(1, 1);
    cm1.print_matrix();
    cm1.resize(30, 30);
    cm1.print_matrix();

    qvec cv5 = rng.gen_randvec(100);
    cv5.print_vec();
    cv5.transpose();
    cv5.print_vec();

    qvec cv = rng.gen_randvec(5);
    // iterator
    for(double c: cv){
        std::cout << "next c = " << c << std::endl;
    }
}

int main(){
    RAND_ENG::RNG rng;
    complexv c_v(q_pi);
    c_v.print(); // note that double represents up to 15 sig figs. Quadruple -> 36 sig figs

    // t1();
    // t2();
    // t3();
    // t4();
    // t5();
    // t6();
    // t7();

    // qmatrix cm_x1 = rng.gen_randmatrix(10, 10);
    // qmatrix cm_x2 = rng.gen_randmatrix(10, 20);
    // qmatrix cm_x1x2 = cm_x1.append(cm_x2, right_d);
    // cm_x1x2.print_matrix();

    // qmatrix cm_x3 = rng.gen_randmatrix(30, 20);
    // qmatrix cm_x4 = rng.gen_randmatrix(1, 1);
    // cquad<qmatrix> cq(cm_x1, cm_x2, cm_x3, cm_x4);

    // for(int i=0; i<4; i++)
    //     cq[i].print_matrix();
    
    // for(qmatrix cm: cq){
    //     cm.print_matrix();
    // }



    return 0;
}
