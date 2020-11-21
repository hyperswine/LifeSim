#pragma once
#include <cstddef>

enum assert_err{
    FATAL_ASSERT = -1,
    BAD_ASSERT = -2
};

class Tester{
protected:
    // we want some measure of accuracy
    size_t test_acc;
    size_t _n_tests;
    size_t n_passed;
    signed int overall_score; // can be pos or neg

    // TODO: have function pointers
    

    // TODO: have an implicit exception catcher, which catches all exceptions
    // but prints the exception and exits.

public:
    Tester();
    void assert_eq(bool); // assert a critical condition -> fatal if not
    void assert_t(bool, int, const char*); // assert non-critical condition -> TODO: error message when failed
    void test_round(int n_tests);

};

class HMathTester: public Tester{
private:
    int x;
public:
    HMathTester();
};

// TODO: unit tester 
class UTest{
private:
    int y;
public:
    UTest(){};
};
