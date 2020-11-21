// Here we evaluate the accuracies and errors of our randomized algorithms against
// their deterministic counterparts
#include "backend.h"
#include <iostream>
#include <string>
#include <cstdarg>
#include <any>

void c_log(std::string x){
    std::cout << x << std::endl;
}

void e_log(const char* str){
    std::cerr << str << std::endl;
}

