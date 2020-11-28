// Here we implement ewald summation of potential energy.
// The idea is to split the long range and short range distances and sum over fourier and real spaces.
// Achieves linear speedup in molecular dynamics.


// the purpose of particle mesh ewald is to sum up the infinitely distanced long-range electrostatic
// energies between the orthogonal 3d-meshes. We use a parallel infinite 3d mesh to simulate inifinite space
// NOTE: for many purposes, this method isn't actually required so simpler boundary conditions can be used instead to simulate a restricted box.
void particle_ewald();
