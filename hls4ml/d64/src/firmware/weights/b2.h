//Numpy array shape [64]
//Min 0.000000000000
//Max 0.000000000000
//Number of zeros 64

#ifndef B2_H_
#define B2_H_

#ifndef __SYNTHESIS__
bias2_t b2[64];
#else
bias2_t b2[64] = {
#include "b2.txt"
};
#endif

#endif