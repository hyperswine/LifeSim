#include "utests_x"
#include "hyper_math/qtensor.h"
#include "hyper_math/fcomplex.h"
#include "hyper_math/hypmath.h"
#include "hyper_math/rng_engine.h"
#include "tester.h"

using namespace RAND_ENG;

RNG _rng;
Tester _tester;

class tfixture_1{
public:
    qvec& qv1 = _rng.gen_randvec(100);
    qvec& qv2 = _rng.gen_randvec(100);
    qmatrix& qm1 = _rng.gen_randmatrix(5, 5);
    qmatrix& qm2 = _rng.gen_randmatrix(5, 5);
    complexv& cpx1 = complexv(4);
    complexv& cpx2 = complexv(2);

    tfixture_1(){

    }
    // call destructor for all variables?
    ~tfixture_1(){
        
    }
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
