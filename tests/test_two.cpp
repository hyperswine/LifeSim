#include <iostream>
#include <string.h>

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

int main(){
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

    return 0;
}
