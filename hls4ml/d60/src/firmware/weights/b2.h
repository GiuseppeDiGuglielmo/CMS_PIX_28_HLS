//Numpy array shape [60]
//Min 0.000000000000
//Max 0.000000000000
//Number of zeros 60

#ifndef B2_H_
#define B2_H_

#ifndef __SYNTHESIS__
static bias2_t b2[60];
#else
static bias2_t b2[60] = {
#include "b2.txt"
};
#endif

#endif
