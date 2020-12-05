#include "C4121"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]){
    int N = 10000;
    // 2*e*n*ln(n)
    int T = 2*N*exp(1)*log(N);
    int succeeded = acc_contention(N, T);

    std::cout << "For N=" << N << " T=" << T << std::endl;
    std::cout << "Number of success = " << succeeded << std::endl;

    return 0;
}
