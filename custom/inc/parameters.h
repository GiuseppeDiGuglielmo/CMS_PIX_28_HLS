#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ac_int.h"
#include "ac_fixed.h"

#include "nnet_activation.h"
#include "defines.h"

// dense1
struct config2 {
    static const unsigned block_size = 2;
    static const unsigned n_in = N_INPUT_1_1;
    static const unsigned n_out = N_LAYER_2;
    typedef ac_fixed<16,6,true> accum_t;
    typedef bias2_t bias_t;
    typedef weight2_t weight_t;
    typedef layer2_t out_t;
};

// dense1_linear
struct linear_config3 : nnet::activ_config {
    static const unsigned n_in = N_LAYER_2;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef ac_fixed<18,8,true> table_t;
};

// relu1
struct relu_config4 : nnet::activ_config {
    static const unsigned n_in = N_LAYER_2;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef ac_fixed<18,8,true> table_t;
};

// dense2
struct config5 {
    static const unsigned block_size = 2;
    static const unsigned n_in = N_LAYER_2;
    static const unsigned n_out = N_LAYER_5;
    typedef ac_fixed<16,6,true> accum_t;
    typedef bias5_t bias_t;
    typedef weight5_t weight_t;
    typedef layer5_t out_t;
};

// dense2_linear
struct linear_config6 : nnet::activ_config {
    static const unsigned n_in = N_LAYER_5;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    typedef ac_fixed<18,8,true> table_t;
};

// softmax
struct softmax_config7 : nnet::activ_config {
    static const unsigned n_in = N_LAYER_5;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    static const unsigned axis = -1;
    static const nnet::softmax_implementation implementation = nnet::softmax_implementation::latency;
    typedef ac_fixed<18,8,true> exp_table_t;
    typedef ac_fixed<18,4,true> inv_table_t;
};


#endif
