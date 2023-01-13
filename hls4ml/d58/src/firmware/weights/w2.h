//Numpy array shape [16, 58]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 56

#ifndef W2_H_
#define W2_H_

#ifndef __SYNTHESIS__
static weight2_t w2[928];
#else
static weight2_t w2[928] = {
#include "w2.txt"
};
#endif

#endif
