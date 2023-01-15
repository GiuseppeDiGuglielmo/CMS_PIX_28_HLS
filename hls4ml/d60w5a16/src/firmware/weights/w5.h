//Numpy array shape [60, 3]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 11

#ifndef W5_H_
#define W5_H_

#ifndef __SYNTHESIS__
static weight5_t w5[180];
#else
static weight5_t w5[180] = {
#include "w5.txt"
};
#endif

#endif
