#ifndef DEFINES_H_
#define DEFINES_H_

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 14
#define N_LAYER_2 128
#define N_LAYER_5 3

//hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<16,6> model_default_t;
typedef ap_fixed<16,6> input_t;
typedef ap_fixed<16,6> layer2_t;
typedef ap_fixed<5,1> weight2_t;
typedef ap_fixed<5,1> bias2_t;
typedef ap_fixed<16,6,AP_RND,AP_SAT> layer3_t;
typedef ap_ufixed<10,0,AP_RND,AP_SAT> layer4_t;
typedef ap_fixed<16,6> layer5_t;
typedef ap_fixed<5,1> weight5_t;
typedef ap_fixed<5,1> bias5_t;
typedef ap_fixed<16,6,AP_RND,AP_SAT> layer6_t;
typedef ap_fixed<16,6> softmax_default_t;
typedef ap_fixed<16,6> result_t;

#endif
