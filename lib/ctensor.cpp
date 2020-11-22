#include "hyper_math/fcomplex.h"
#include "hyper_math/ctensor.h"
#include <cmath>
#include <iostream>

#define init_vec(n) column_vec = true; vec = new complexv[n]; cur_size = n;

// create a length 1 column vector
cvec::cvec(){
    init_vec(1);
}
cvec::cvec(int n){
    init_vec(n);
}
cvec::~cvec(){
    delete[] vec;
}

void cvec::print_vec(){
    if(column_vec){
        std::cout << "==Column vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++){
            std::cout.precision(2); 
            std::cout << std::scientific << vec[i].re() << " i*" << vec[i].im() << std::endl;
        }
    }
    else{
        std::cout << "==Row vector, size: " << cur_size << std::endl;
        for(int i=0; i<cur_size; i++){
            std::cout.precision(2); 
            std::cout << std::scientific << " " << vec[i].re() << " i*" << vec[i].im();
        }
        std::cout << std::endl;
    }
    std::cout << "==End vector\n" << std::endl;
}

complexv cvec::operator*(const cvec& oth_vec){
    if(cur_size != oth_vec.cur_size) throw -1; // replace -1 with macro

    complexv res;
    for(int i=0; i<cur_size; i++){
        res += vec[i] * oth_vec[i];
    }

    return res;
}
complexv& cvec::operator[](int& i) const{
    if(abs(i) >= cur_size) throw -1;

    int indexer = i % cur_size;
    return vec[indexer];
}
complexv& cvec::operator[](int&& i) const{
    if(abs(i) >= cur_size) throw -1;

    int indexer = i % cur_size;
    return vec[indexer];
}
