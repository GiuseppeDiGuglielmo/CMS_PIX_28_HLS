//Numpy array shape [64, 3]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 11

#ifndef W5_H_
#define W5_H_

#ifndef __SYNTHESIS__
weight5_t w5[192];
#else
weight5_t w5[192] = {
#include "w5.txt"
};
#endif

#endif
