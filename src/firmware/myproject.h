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

#ifndef MYPROJECT_H_
#define MYPROJECT_H_

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

#include "defines.h"

// Prototype of top level function for C-synthesis
void myproject(
    input_t input_1[N_INPUT_1_1],
    result_t layer6_out[N_LAYER_5]
#if defined(V03)
    ,
    weight2_t w2[1792],
    bias2_t b2[128],
    weight5_t w5[384],
    bias5_t b5[3]
#endif
);

#endif
