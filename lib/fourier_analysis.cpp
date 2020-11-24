#include "hyper_math/fourier_field.h"
#include "hyper_math/ctensor.h"
#include "hyper_math/hypmath.h"
#include "backend.h"
#include <cmath>

#define IS_INT(x) (std::floor(x) == x)

/**
 * Brute force DFT O(n^2). Based on the fact that x(hat)_k = sum(x_k * e^{-i*2pi*k*j/N} for j=0..N-1)
 * NOTE: if N is not a power of 2, then this will append extra zeros until it reaches the next power of 2
 */
cvec dft(const qvec& x){
    int N = x.len();
    if( !IS_INT(log2(N)) ){
        // common way to find next power. Not as fast, but works.
        N = pow(2, ceil(log2(N)));
    }

    cvec dft_res(N);

    for(int k=0; k<N; k++){
        for(int j=0; j<N; j++){
            complexv temp(-2*c_pi*k*j/N);
            // dft_res[k] += x[j] * temp;
        }
    }

    return dft_res;
}

// Inverse DFT
qvec inverse_dft(const cvec& x){
    return qvec(1);
}

/**
 * In - x, points sampled from some function f. NOTE: x here is the f(x) terms, unless an overload is used to provide a function.
 * Keeping dividing x in half until N = 2, then compute DFT of x in O(1) -> log(n)
 * Doing the above for the entirety of x -> O(n). Recombining where each scan takes log(n) -> O(nlogn) total
 */
cvec fft_v1(const qvec& x){
    int N = x.len();
    // quick append -> happens at most once on call
    if(!IS_INT(log2(N))) N = pow(2, ceil(log2(N)));
    
    cvec res(N);
    // base condition
    if(N == 2) res = dft(x);
    
    // the magic
    else{
        // call fft on even terms
        cvec _even = fft_v1(x[EVEN_T]);
        // call fft on odd terms
        cvec _odd = fft_v1(x[ODD_T]);
    
        // join them together in order
        for(int k=0; k<N; k++){
            if(k%2==0)
                res[k] += _even[k/2] * complexv(-2*c_pi*k/N);
            else
                res[k] += _odd[k/2] * complexv(-2*c_pi*k/N);
        }

    }
    // return the dft from 0..N (current N)
    return res;
}

// Take in a series of points and a function that maps the points
// Returns the DFT of {f} on {x}
// cvec fft_v2(const qvec& x, (void*)(quadruple) f_x){
//     qvec mapped_f(x.len());

//     // apply f_x to all x
//     for(int i=0; i<x.len(); i++) mapped_f[i] = f_x(x[i]);

//     // return result of fft
//     return fft_v1(mapped_f);
// }
