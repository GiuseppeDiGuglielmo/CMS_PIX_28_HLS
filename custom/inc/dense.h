#ifndef NNET_DENSE_H_
#define NNET_DENSE_H_

#include "nnet_common.h"
#include "nnet_helpers.h"
#include "ac_channel.h"
#include <math.h>

#if defined(V05) || defined(V06) || defined(V07) || defined(V08) || defined(V09)
// CCORE
template<class data_T, class res_T, typename CONFIG_T>
typename CONFIG_T::accum_t accum_inner_func(
        data_T inputs[CONFIG_T::block_size],
        typename CONFIG_T::weight_t weights[CONFIG_T::block_size])
{
    typename CONFIG_T::accum_t accum = 0;
ACCUM_INNER_LOOP:
    for (unsigned j = 0; j < CONFIG_T::block_size; j++) {
        accum += inputs[j] * weights[j];
    }
    return accum;
}
#endif

#pragma hls_design block
template<class data_T, class res_T, typename CONFIG_T>
void dense(
    data_T    inputs[CONFIG_T::n_in],
    res_T     results[CONFIG_T::n_out],
    typename CONFIG_T::weight_t  weights[CONFIG_T::n_out][CONFIG_T::n_in],
    typename CONFIG_T::bias_t    biases[CONFIG_T::n_out])
{
#if defined(V04)
ACCUM_OUTER_LOOP:
    for (unsigned j = 0; j < CONFIG_T::n_out; j++) {
        typename CONFIG_T::accum_t accum = biases[j];
ACCUM_INNER_LOOP:
        for (unsigned i = 0; i < CONFIG_T::n_in; i++) {
            accum += inputs[i] * weights[j][i];
        }
        results[j] = accum;
    }

#elif defined(V05) || defined(V06) || defined(V07) || defined(V08) || defined(V09)

ACCUM_OUTER_LOOP:
    for (unsigned j = 0; j < CONFIG_T::n_out; j++) {
        typename CONFIG_T::accum_t accum = biases[j];
ACCUM_INNER_LOOP:
        for (unsigned i = 0; i < (CONFIG_T::n_in / CONFIG_T::block_size); i++) {
            accum += accum_inner_func<data_T, res_T, CONFIG_T>(inputs + i*CONFIG_T::block_size, weights[j] + i*CONFIG_T::block_size);
        }
        results[j] = accum;
    }

#endif
}

#endif
