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
    hsingle<> hs;
    hs.print();

    std::cout << "Succesfully created hsingle and called hs.print()\n";

    hmatrix<> hm;
    hm.print();
    std::cout << hm(0,0) << " " << hm(0,1) << " " << hm(1,0) << " " << hm(1,1) << std::endl;

    std::cout << "Succesfully created hmatrix and called hm.print()\n";
}

TEST(generic, one){
    std::cout << "pth root of 1000: " << p_root(1000, 5) << std::endl;
}
