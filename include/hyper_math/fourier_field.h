#pragma once
#include "fcomplex.h"
#include "ctensor.h"
#include "qtensor.h"
#include "hyp_math.h"

// slow dft. No requirements, thought would be great if points were evenly spaced out and were sequential
cvec dft(const qvec&);
qvec inverse_dft(const cvec&);
