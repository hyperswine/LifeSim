#include <iostream>
#include "tester.h"
#include "jparallel.h"
#include "hyper_math/rng_engine.h"
// add lin_alg and complex later

class A{
private:
    int a;
    int* b;

    int** z;
public:
    A(int x){
        a = x;
        // b = new int;make
        // *z = new int[x];
    }
    ~A(){
        // delete b;
        // delete z;
    }
    void print();
    int get_a() const{
        return a;
    }
    void assert_x(bool x);
};

void A::assert_x(bool x){
    if(!x){
        std::cerr << "assertion failed" << std::endl;
        throw FATAL_ASSERT;
    }
}

void A::print(){
    using namespace std;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
}

// default sanity tests
int main(){
    Tester* tester = new Tester();

    // sanity checks
    tester->assert_eq(0 == 0);
    tester->assert_t(0 == 0, __LINE__, __FILE__);

    // test whether our random generator engine works
    using namespace RAND_ENG;
    RNG* rng = new RNG();
    double y = rng->gen_double();
    int x = rng->gen_int(0, 1);

    tester->assert_eq(x <= 1 && x >= 0);
    tester->assert_t(x <= 1 && x >= 0, __LINE__, __FILE__);

    std::cout << "y = " << y << std::endl;
    std::cout << "x = " << x << std::endl;

    return 0;
}
