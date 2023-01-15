//Numpy array shape [14, 128]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 254

#ifndef W2_H_
#define W2_H_

#ifndef __SYNTHESIS__
weight2_t w2[1792];
#else
weight2_t w2[1792] = {
#include "w2.txt"
};
#endif

#endif
