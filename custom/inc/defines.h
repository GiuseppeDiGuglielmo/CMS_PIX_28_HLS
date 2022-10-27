#ifndef DEFINES_H_
#define DEFINES_H_

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 14
#define N_LAYER_2 128
#define N_LAYER_5 3

//hls-fpga-machine-learning insert layer-precision
typedef ac_fixed<16,6,true> model_default_t;
typedef ac_fixed<16,6,true> input_t;
typedef ac_fixed<16,6,true> layer2_t;
typedef ac_fixed<5,1,true> weight2_t;
typedef ac_fixed<5,1,true> bias2_t;
typedef ac_fixed<16,6,true,AC_RND_CONV,AC_SAT> layer3_t;
typedef ac_fixed<10,0,false,AC_RND_CONV,AC_SAT> layer4_t;
typedef ac_fixed<16,6,true> layer5_t;
typedef ac_fixed<5,1,true> weight5_t;
typedef ac_fixed<5,1,true> bias5_t;
typedef ac_fixed<16,6,true> result_t;
//typedef ac_fixed<16,6,true,AC_RND_CONV,AC_SAT> layer6_t;
//typedef ac_fixed<16,6,true> softmax_default_t;
//typedef ac_fixed<16,6,true,AC_RND_CONV,AC_SAT> result_t;

//typedef ac_fixed<128,64,true> model_default_t;
//typedef ac_fixed<128,64,true> input_t;
//typedef ac_fixed<128,64,true> layer2_t;
//typedef ac_fixed<128,64,true> weight2_t;
//typedef ac_fixed<128,64,true> bias2_t;
//typedef ac_fixed<128,64,true,AC_RND_CONV,AC_SAT> layer3_t;
//typedef ac_fixed<128,64,false,AC_RND_CONV,AC_SAT> layer4_t;
//typedef ac_fixed<128,64,true> layer5_t;
//typedef ac_fixed<128,64,true> weight5_t;
//typedef ac_fixed<128,64,true> bias5_t;
//typedef ac_fixed<128,64,true,AC_RND_CONV,AC_SAT> layer6_t;
//typedef ac_fixed<128,64,true> softmax_default_t;
//typedef ac_fixed<128,64,true,AC_RND_CONV,AC_SAT> result_t;


#endif
