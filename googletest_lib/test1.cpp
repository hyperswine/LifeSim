#include "gtest/gtest.h"
#include "hmath"

#include <iostream>

TEST(dft_tests, dft) {
    qvec in(16);
    in.print_vec();
    cvec out = dft(in);
    out.print_vec();
}

TEST(htensors, h1){
    hsingle<int> hs;
    hs.print();

    std::cout << "Succesfully created hsingle and called hs.print()\n";
}
