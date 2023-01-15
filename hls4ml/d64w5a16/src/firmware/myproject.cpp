//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>

#include "myproject.h"
#include "parameters.h"

#include <mc_scverify.h>

result_t argmax(layer6_t layer6_out[N_LAYER_6]) {
    if (layer6_out[0] >= layer6_out[1] && layer6_out[0] >= layer6_out[2]) return 0;
    else if (layer6_out[1] >= layer6_out[0] && layer6_out[1] >= layer6_out[2]) return 1;
    else return 2;
}

#pragma hls_design top
//hls-fpga-machine-learning insert IFSynPragmas
void CCS_BLOCK(myproject)(
    input_t input_1[N_INPUT_1_1],
    result_t &layer7_out
#if defined(V03)
    ,
    weight2_t w2[1024],
    bias2_t b2[64],
    weight5_t w5[192],
    bias5_t b5[3]
#endif
) {

    //hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=input_1 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer7_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=input_1,layer7_out
    #pragma HLS PIPELINE

#if defined(V01) || defined(V02)
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        //hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<weight2_t, 1024>(w2, "w2.txt");
        nnet::load_weights_from_txt<bias2_t, 64>(b2, "b2.txt");
        nnet::load_weights_from_txt<weight5_t, 192>(w5, "w5.txt");
        nnet::load_weights_from_txt<bias5_t, 3>(b5, "b5.txt");
        loaded_weights = true;
    }
#endif
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    layer2_t layer2_out[N_LAYER_2];
    #pragma HLS ARRAY_PARTITION variable=layer2_out complete dim=0
    nnet::dense<input_t, layer2_t, config2>(input_1, layer2_out, w2, b2); // dense1

    layer3_t layer3_out[N_LAYER_2];
    #pragma HLS ARRAY_PARTITION variable=layer3_out complete dim=0
    nnet::linear<layer2_t, layer3_t, linear_config3>(layer2_out, layer3_out); // dense1_linear

    layer4_t layer4_out[N_LAYER_2];
    #pragma HLS ARRAY_PARTITION variable=layer4_out complete dim=0
    nnet::relu<layer3_t, layer4_t, relu_config4>(layer3_out, layer4_out); // relu1

    layer6_t layer6_out[N_LAYER_6];
    #pragma HLS ARRAY_PARTITION variable=layer6_out complete dim=0
    nnet::dense<layer4_t, layer6_t, config6>(layer4_out, layer6_out, w5, b5); // dense2

    layer7_out = argmax(layer6_out);

//    nnet::softmax<layer6_t, result_t, softmax_config7>(layer6_out, layer7_out); // softmax

}
