// monte carlo algorithm declarations. May not be required.
#pragma once
#include "hyper_math/qtensor.h"

quadruple sample_I(const qvec& input);
quadruple sample_mc_integral(int n_gen);
quadruple mc_integral(int n_gen);
