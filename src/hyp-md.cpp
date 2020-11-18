#include <vector>
#include "md.h"
#include <iostream>
using namespace std;

void do_execute(){
    if(1 == 0){
        throw -20;
    }
    std::cout << "Welcome to the Hyper Sim" << std::endl;
}

vector<double> ele_addition(vector<double> a, vector<double> b) {
    vector<double> new_vec;
    for (int i = 0; i < a.size(); i++) {
        new_vec[i] = a[i] + b[i];
    }

    return new_vec;
}

/**
 * Type = 0 for inner product (f: R^nxR^n -> R^1)
 */
// double c_reduce(vector<double> vec1, vector<double> vec2, int type) {
//     double prod = 0.0;
//     for (int i = 0; i < vec1.size(); i++) {
//         prod += (vec1[i] * vec2[i]);
//     }

//     return prod;
// }

// // define our own energy function
// double energy_u(vector<double> r, vector<double> v) {
//     vector<double> u;
//     for (int i = 0; i < r.size(); i++) {
//         u.push_back(rand());
//     }
    
//     return c_reduce(ele_addition(r, v), u, 0);
// }

// // initialize a vector to random values between a range given a length
// void init_vec(vector<vector<double>> &vec, int len, double a, double b) {
//     random_device rd{};
//     mt19937 gen{ rd() };
//     uniform_real_distribution<double> dist;

//     for (int i = 0; i < len; i++) {
//         vector<double> temp(3);
//         vec.push_back(temp);
//         for (int j = 0; j < 3; j++)
//             vec[i][j] = (dist(gen));
//     }
// }

// int main() {
//     int n_steps = 1000;
//     const int n_particles = 100;
//     vector<vector<double>> r;
//     vector<vector<double>> v;
//     vector<vector<double>> a;
//     vector<double> potentials; // same as below
//     vector<double> f; // completely overwritten at each atom iteration 

//     init_vec(r, n_particles, 0, 100);

//     for (int i = 0; i<n_particles; i++) {
//         for (int j = 0; j<3; j++)
//             cout << r[i][j] << endl;
//     }
//     //cout << energy_u() << endl;


//     for (int i = 0; i < n_steps; i++) {
//          for (int j = 0; j < n_particles; j++) {
//              return 1;
//              // v[j] = integrate accelerations
//              // r[j] = integrate velocities

//              // potentials[j] = energy(r)
//          }
//     }

//     // local search energy estimation

//     return 0;

// }
