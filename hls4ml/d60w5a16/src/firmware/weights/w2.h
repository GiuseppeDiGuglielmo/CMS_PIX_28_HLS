//Numpy array shape [16, 60]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 47

#ifndef W2_H_
#define W2_H_

#ifndef __SYNTHESIS__
static weight2_t w2[960];
#else
static weight2_t w2[960] = {
#include "w2.txt"
};
#endif

#endif
