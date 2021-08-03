#include "hmath"

#define IS_INT(x) (std::floor(x) == x)
// C unfortunately compiles char*/strings as ints. This is a temporary solution.
const ODD_EVEN even_t{true};
const ODD_EVEN odd_t{false};

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

    for(int k=0; k<N; k++)
        for(int j=0; j<N; j++){
            dft_res[k] += complexv(-2*c_pi*k*j/N) * ((double)x[j]);
        }

    return dft_res;
}

/**
 * Tensor-based DFT -> works on hvecs.
 * O(n^2), note if always calling dft(x) on a constant size x, then O(1)
 */
hvec<complexv> dft(const hvec<>& x){
    int N = x.len();
    if( !IS_INT(log2(N)) ){
        // common way to find next power. Not as fast, but works.
        N = pow(2, ceil(log2(N)));
        x.resize(N);
    }

    hvec<complexv> dft_res(N);

    for(int k=0; k<N; k++)
        for(int j=0; j<N; j++){
            dft_res[k] += complexv(-2*c_pi*k*j/N) * ((double)x[j]);
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
    if(!IS_INT(log2(N))){
        N = pow(2, ceil(log2(N)));
        x.resize(N);
    }
    
    if(N == 2) return dft(x);
    
    // the magic
    else{
        cvec res(N);
        // call fft on even terms
        cvec _even = fft_v1(x[even_t]);
        // call fft on odd terms
        cvec _odd = fft_v1(x[odd_t]);
    
        complexv w(1, 0);
        // join them together
        for(int k=0; k<N/2; k++){
            res[k] += _even[k] + _odd[k] * w;
            res[N/2+k] += _even[k] +_odd [k] * w;
            w = complexv(2*c_pi*k/N) * w;
        }
        return res;
    }    
}



hvec<> fft_v2(const hvec<>& x){
    int N = x.len();
    // quick append -> happens at most once on call
    if(!IS_INT(log2(N))) N = pow(2, ceil(log2(N)));
    
    if(N == 2) return dft(x);
    
    // the magic
    else{
        hvec<> res(N);
        // call fft on even terms
        hvec<> _even = fft_v1(x[even_t]);
        // call fft on odd terms
        hvec<> _odd = fft_v1(x[odd_t]);
    
        complexv w(1, 0);
        // join them together
        for(int k=0; k<N/2; k++){
            res[k] += _even[k] + _odd[k] * w;
            res[N/2+k] += _even[k] +_odd [k] * w;
            w = complexv(2*c_pi*k/N) * w;
        }
        return res;
    }
}

// Take in a series of points and a function that maps the points
// Returns the DFT of {f} on {x}
// cvec fft_v3(const qvec& x, (void*)(quadruple) f_x){
//     qvec mapped_f(x.len());

//     // apply f_x to all x
//     for(int i=0; i<x.len(); i++) mapped_f[i] = f_x(x[i]);

//     // return result of fft
//     return fft_v1(mapped_f);
// }
