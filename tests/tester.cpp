#include "tester.h"
#include <iostream>

Tester::Tester(){
    overall_score = 0;
}

void Tester::assert_eq(bool cond){
    if(!cond) throw FATAL_ASSERT;
}

void Tester::assert_t(bool cond, int line, const char* file){
    if(!cond){
        std::cout << "---------------------------" << std::endl;
        std::cout << "  Non-critical test failed...  " << std::endl;
        std::cout << "Line: " << line << ", File: " << file << std::endl;
        std::cout << "---------------------------" << std::endl;
    }
    else{
        std::cout << "----------" << std::endl;
        std::cout << "  PASSED  " << std::endl;
        std::cout << "----------" << std::endl;
    }
}

// set up a 'round' of testing of n tests
void Tester::test_round(int n_tests){
    _n_tests = n_tests;
}
