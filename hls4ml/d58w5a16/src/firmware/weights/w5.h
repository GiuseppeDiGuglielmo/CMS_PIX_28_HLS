//Numpy array shape [58, 3]
//Min -0.875000000000
//Max 0.937500000000
//Number of zeros 8

#ifndef W5_H_
#define W5_H_

#ifndef __SYNTHESIS__
static weight5_t w5[174];
#else
static weight5_t w5[174] = {
#include "w5.txt"
};
#endif

#endif
