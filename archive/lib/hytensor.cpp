#include "hyper_math/htensor"

#include <iostream>

// FOR HTENSOR UTILITIES and etc. definitions

void matrix_splitter(hmatrix<> M, ...){
    va_list args;
    va_start(args, M);

    for(int i=0; i<M.cols(); i++){
        hvec<> x = va_arg(args, hvec<>);
    }

    va_end(args);
}
