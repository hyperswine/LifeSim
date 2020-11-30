#include "utests_x"
#include "hyper_math/qtensor.h"
#include "hyper_math/ctensor.h"
#include "hyper_math/fcomplex.h"
#include "hyper_math/fourier_field.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/rng_engine.h"
#include "tester.h"
#include <iostream>

using namespace RAND_ENG;

RNG _rng;
Tester _tester;

class tfixture_1{
public:
    qvec qv1 = _rng.gen_randvec(100);
    qvec qv2 = _rng.gen_randvec(100);
    qvec qv3 = _rng.gen_randvec(5);
    qmatrix qm1 = _rng.gen_randmatrix(5, 5);
    qmatrix qm2 = _rng.gen_randmatrix(5, 5);
    complexv cpx1 = complexv(4);
    complexv cpx2 = complexv(2);
    cvec cv1 = cvec(10);
    cvec cv2 = cvec(10);

    tfixture_1(){}
    ~tfixture_1(){}
};


class tfixture_dft{
public:
    cvec cv1 = _rng.gen_cvec(10);
    cvec cv2 = _rng.gen_cvec(16, -1, 1);
    cvec cv3 = cvec(10);
    qvec qv1 = _rng.gen_randvec(16, -1, 1);
    qvec qv2 = _rng.gen_normvec(16, 0, 1);

    tfixture_dft(){}
    ~tfixture_dft(){}
};

void test_basic(){
    tfixture_1 _t;
    qvec qv1(10);
    qvec qv2(10);

    quadruple res = qv1 * qv2;
    _tester.assert_eq(res == 0);

    _t.qv1.print_vec();

    cpair<qvec> cp(qv1, qv2);
    cp[0].print_vec();
    cp[1].print_vec();
}

void test_two(){
    tfixture_1 _t;
    _t.qm2.print_matrix();
    _t.qv3.print_vec();

    qvec res = _t.qm2 * _t.qv3;
    res.print_vec();
}

void test_complex_basic(){
    tfixture_1 _t;
    _t.cv1.print_vec();
    _t.cv2.print_vec();

    complexv cv_res = _t.cv1 * _t.cv2;
    cv_res.print();
}

tfixture_dft _t_global;

void test_dft(){
    // tfixture_dft _t;
    // _t.qv2.print_vec();

    // cvec res = dft(_t.qv2);
    // res.print_vec();

    _t_global.qv2.print_vec();
    dft(_t_global.qv2).print_vec();
}

void test_fft(){
    // tfixture_dft _t;
    // _t.qv2.print_vec();

    // cvec res = fft_v1(_t.qv2);
    // res.print_vec();

    _t_global.qv2.print_vec();
    fft_v1(_t_global.qv2).print_vec();
}
