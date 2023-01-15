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
#define N_LAYER_2 64
#define N_LAYER_6 3
#define N_LAYER_5 3

//hls-fpga-machine-learning insert layer-precision
//typedef ac_fixed<16,8,true> model_default_t;
typedef ac_int<6,false> input_t;
typedef ac_fixed<8,5,true> layer2_t;
typedef ac_fixed<4,1,true> weight2_t;
typedef ac_fixed<4,1,true> bias2_t;
typedef ac_fixed<16,8,AP_RND,AP_SAT> layer3_t;
typedef ac_fixed<8,0,false,AC_RND_CONV,AC_SAT> layer4_t;
typedef ac_fixed<10,6,true> layer5_t;
typedef ac_fixed<4,1,true> weight5_t;
typedef ac_fixed<4,1,true> bias5_t;
typedef ac_fixed<16,8,true> layer6_t;
typedef ac_fixed<16,6,true> softmax_default_t;
typedef ac_int<2,false> result_t;

#endif
