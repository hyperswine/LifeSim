#pragma once
#include "fcomplex.h"
#include "ctensor.h"
#include "qtensor.h"
#include "hypmath.h"

// slow dft. No requirements, thought would be great if points were evenly spaced out and were sequential
cvec dft(const qvec&);
qvec inverse_dft(const cvec&);
cvec fft_v1(const qvec& x);
