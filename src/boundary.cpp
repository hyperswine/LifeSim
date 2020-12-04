// Boundary conditions -> reflective boundary or periodic boundary.
// note: ewald summation required for large simulation boxes with electrostatic forces
#include "hmath"

/**
 * Apply a reflective force that pushes particles into the middle
 */
void apply_reflective(){
    return;
}

/**
 * Initialize k three-dimensional cells of N atoms each.
 * Main cell is always 0th indexed
 */
CELL_LIST* initialize_cells(int N, int k_cells){
    CELL_LIST* cl = new CELL_LIST;
    cl->all_cells = new CELL[k_cells];
    cl->N = N;

    return cl;
}

/**
 * When a particle goes out of the simulation box, i.e. steps outside at least 1 of the x, y or z coordinates,
 * particle must appear in the new cell. Its location in the new cell is copied to every other cell
 * 
 * Works on a 3D-lattice of 9 cells, 8 of which are simply copies.
 */
void periodic_boundary(){
    return;
}
