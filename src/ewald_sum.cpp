// Here we implement ewald summation of potential energy.
// The idea is to split the long range and short range distances and sum over fourier and real spaces.
// Achieves linear speedup in molecular dynamics.
#include "hmath"
#include "md.h"
#include "hypmd"

/**
 * In - r_p, cutoff distance between shorter and longer ranges
 * Out - 2xn Matrix, 1st column contains short ranges, 2nd column contains long ranges.
 */
hmatrix<> rc_split(quadruple r_p, hvec<>);

/**
 * In - the working particle and all the other particles in the nearest image
 */
void ewald_sum(hmatrix<> distances){
    // split into longer ranged and shorter ranged distances, using r_p as a cutoff
    hvec<> s_range;
    hvec<> l_range;

    matrix_splitter(distances, s_range, l_range);

    // compute short ranged energies in real space

}

// the purpose of particle mesh ewald is to sum up the infinitely distanced long-range electrostatic
// energies between the orthogonal 3d-meshes. We use a parallel infinite 3d mesh to simulate inifinite space
void particle_ewald();

// NOTE: for many purposes, this method isn't actually required so simpler boundary conditions can be used instead to simulate a restricted box.

/**
 * In - two position vectors, r_i, r_j
 *    - cell list
 * Out - cell k, where the nearest r_j(k) is to the main r_i
 */
int nearest_image(CELL_LIST* cl, int i, int j){
    // cell that contains minimum distance between r_i and r_j.
    // By default start with main cell
    int k_min = 0;
    quadruple d_min = dist(cl[0]->M[i], cl[1]->M[j];
    for(int i=0; i<cl->k_cells; i++){
        if(dist(c->M[i], c->M[j]) < d_min){
            k_min = i;
        }
    }

    return k_min;
}
