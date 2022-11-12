//Numpy array shape [128, 3]
//Min -1.000000000000
//Max 0.937500000000
//Number of zeros 13

#ifndef W5_H_
#define W5_H_

#ifndef __SYNTHESIS__
weight5_t w5[384];
#else
weight5_t w5[384] = {
#include "w5.txt"
};
#endif

#endif
