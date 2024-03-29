#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ac_int.h"
#include "ac_fixed.h"

#include "nnet_utils/nnet_helpers.h"
//hls-fpga-machine-learning insert includes
#include "nnet_utils/nnet_activation.h"
#include "nnet_utils/nnet_activation_stream.h"
#include "nnet_utils/nnet_dense.h"
//#include "nnet_utils/nnet_dense_compressed.h"
//#include "nnet_utils/nnet_dense_stream.h"
 
//hls-fpga-machine-learning insert weights
#include "weights/w2.h"
#include "weights/b2.h"
#include "weights/w5.h"
#include "weights/b5.h"

//hls-fpga-machine-learning insert layer-config
// dense1
struct config2 : nnet::dense_config {
    static const unsigned n_in = N_INPUT_1_1;
    static const unsigned n_out = N_LAYER_2;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    //static const unsigned n_zeros = 47;
    //static const unsigned n_nonzeros = 913;
    static const bool merged_relu = false;
    static const bool store_weights_in_bram = false;
    typedef ac_fixed<10,5,true> accum_t;
    typedef bias2_t bias_t;
    typedef weight2_t weight_t;
    typedef ac_int<1,false> index_t;
    //typedef layer2_t:: value_type out_t;
    typedef layer2_t out_t;
    template<class x_T, class y_T, class res_T>
    using product = nnet::product::mult<x_T, y_T>;
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
struct config6 : nnet::dense_config {
    static const unsigned n_in = N_LAYER_2;
    static const unsigned n_out = N_LAYER_5;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned strategy = nnet::latency;
    static const unsigned reuse_factor = 1;
    //static const unsigned n_zeros = 11;
    //static const unsigned n_nonzeros = 169;
    static const bool merged_relu = true;
    static const bool store_weights_in_bram = false;
    typedef ac_fixed<13,5,true> accum_t;
    typedef bias5_t bias_t;
    typedef weight5_t weight_t;
    typedef ac_int<1,false> index_t;
    //typedef layer6_t:: value_type out_t;
    typedef layer6_t out_t;
    template<class x_T, class y_T, class res_T>
    using product = nnet::product::mult<x_T, y_T>;
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
    static const unsigned n_in = N_LAYER_6;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_parallel;
    static const unsigned reuse_factor = 1;
    static const unsigned axis = -1;
    static const nnet::softmax_implementation implementation = nnet::softmax_implementation::latency;
    typedef ac_fixed<18,8,true> exp_table_t;
    typedef ac_fixed<18,4,true> inv_table_t;
};


#endif
