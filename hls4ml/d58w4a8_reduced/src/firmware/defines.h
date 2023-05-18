#ifndef DEFINES_H_
#define DEFINES_H_

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 16
#define N_LAYER_2 58
#define N_LAYER_5 3

//hls-fpga-machine-learning insert layer-precision
typedef ac_fixed<6,6,false> input_t;
typedef ac_fixed<10,5,true> dense1accum_t;
typedef ac_fixed<10,5,true> layer2_t;
typedef ac_fixed<4,1,true> weight2_t;
typedef ac_fixed<4,1,true> bias2_t;
typedef ac_int<1, false> layer2_index;
typedef ac_fixed<10,5,true,AC_RND_CONV,AC_SAT> layer3_t;
typedef ac_fixed<18,8,true> dense1_linear_table_t;
typedef ac_fixed<8,0,false,AC_RND_CONV,AC_SAT> layer4_t;
typedef ac_fixed<18,8,true> relu1_table_t;
typedef ac_fixed<10,4,true> dense2accum_t;
typedef ac_fixed<10,4,true> layer5_t;
typedef ac_fixed<4,1,true> weight5_t;
typedef ac_fixed<4,1,true> bias5_t;
typedef ac_int<1, false> layer5_index;
typedef ac_fixed<10,4,true,AC_RND_CONV,AC_SAT> layer6_t;
typedef ac_fixed<18,8,true> dense2_linear_table_t;
//typedef ac_fixed<16,6,true,AC_RND_CONV,AC_SAT> result_t;
typedef ac_fixed<18,8,true> linear_table_t;
typedef ac_int<2,false> result_t;


#endif
