//Numpy array shape [3]
//Min -0.375000000000
//Max 0.250000000000
//Number of zeros 0

#ifndef B5_H_
#define B5_H_

#ifndef __SYNTHESIS__
static bias5_t b5[3];
#else
static bias5_t b5[3] = {
#include "b5.txt"
};
#endif

#endif
