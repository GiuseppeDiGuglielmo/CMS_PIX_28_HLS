//Numpy array shape [128]
//Min 0.000000000000
//Max 0.000000000000
//Number of zeros 128

#ifndef B2_H_
#define B2_H_

#ifndef __SYNTHESIS__
bias2_t b2[128];
#else
bias2_t b2[128] = {
#include "b2.txt"
};
#endif

#endif
