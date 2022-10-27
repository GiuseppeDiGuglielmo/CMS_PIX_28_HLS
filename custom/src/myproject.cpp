#include <iostream>

#include "myproject.h"
#include "parameters.h"

#include "dense.h"
#include <mc_scverify.h>

#pragma hls_design top
void CCS_BLOCK(myproject)(
    input_t input_1[N_INPUT_1_1],
    result_t layer5_out[N_LAYER_5],
    weight2_t w2[128][14],
    bias2_t b2[128],
    weight5_t w5[3][128],
    bias5_t b5[3]
) {

    layer2_t layer2_out[N_LAYER_2];
    dense<input_t, layer2_t, config2>(input_1, layer2_out, w2, b2); // dense1

//    layer3_t layer3_out[N_LAYER_2];
//    nnet::linear<layer2_t, layer3_t, linear_config3>(layer2_out, layer3_out); // dense1_linear

    layer4_t layer4_out[N_LAYER_2];
    nnet::relu<layer2_t, layer4_t, relu_config4>(layer2_out, layer4_out); // relu1

    //layer5_t layer5_out[N_LAYER_5];
    dense<layer4_t, result_t, config5>(layer4_out, layer5_out, w5, b5); // dense2

//    layer6_t layer6_out[N_LAYER_5];
//    nnet::linear<layer5_t, result_t, linear_config6>(layer5_out, layer6_out); // dense2_linear

//    nnet::softmax<layer6_t, result_t, softmax_config7>(layer6_out, layer7_out); // softmax

}
