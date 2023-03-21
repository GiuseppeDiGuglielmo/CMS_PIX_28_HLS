#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "firmware/myproject.h"
#include "firmware/nnet_utils/nnet_helpers.h"

#include <mc_scverify.h>

//hls-fpga-machine-learning insert bram

////hls-fpga-machine-learning insert declare weights
#include "weights/w2.h"
#include "weights/b2.h"
#include "weights/w5.h"
#include "weights/b5.h"


#define CHECKPOINT 1

namespace nnet {
    bool trace_enabled = true;
    std::map<std::string, void *> *trace_outputs = NULL;
    size_t trace_type_size = sizeof(double);
}

template <class T, int N, int MIN>
unsigned argmax(T args[N]) {
  unsigned max_idx = 0;
  T max = MIN;
//  max.set_val<AC_VAL_MIN>();
  for (unsigned i = 0; i < N; i++) {
    if(args[i] > max) {
      max = args[i];
      max_idx = i;
    }
  }
  return max_idx;
}

template <int N>
unsigned argmax_vector(std::vector<float> args) {
  unsigned max_idx = 0;
  float max = std::numeric_limits<float>::min();
  for (unsigned i = 0; i < N; i++) {
    if(args[i] > max) {
      max = args[i];
      max_idx = i;
    }
  }
  return max_idx;
}


CCS_MAIN(int argc, char *argv[])
{
  //load input data from text file
  std::ifstream fin("tb_data/tb_input_features.dat");
  //load predictions from text file
  std::ifstream fpr("tb_data/tb_output_predictions.dat");

#ifdef RTL_SIM
  std::string RESULTS_LOG = "tb_data/rtl_cosim_results.log";
#else
  std::string RESULTS_LOG = "tb_data/csim_results.log";
#endif
  std::ofstream fout(RESULTS_LOG);

#if defined(V03)
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


  std::string iline;
  std::string pline;
  unsigned errors = 0;
  unsigned outputs = 0;

  if (fin.is_open() && fpr.is_open()) {
    while ( std::getline(fin,iline) && std::getline (fpr,pline) ) {
      char* cstr=const_cast<char*>(iline.c_str());
      char* current;
      std::vector<float> in;
      current=strtok(cstr," ");
      while(current!=NULL) {
        in.push_back(atof(current));
        current=strtok(NULL," ");
      }
      cstr=const_cast<char*>(pline.c_str());
      std::vector<float> pr;
      current=strtok(cstr," ");
      while(current!=NULL) {
        pr.push_back(atof(current));
        current=strtok(NULL," ");
      }

      //hls-fpga-machine-learning insert data
      input_t input_1[N_INPUT_1_1];
      nnet::copy_data<float, input_t, 0, N_INPUT_1_1>(in, input_1);
      result_t layer7_out;

      //hls-fpga-machine-learning insert top-level-function
      unsigned short size_in1,size_out1;
      myproject(input_1,layer7_out
#if defined(V03)
              , w2, b2, w5, b5
#endif
              );
#ifdef VERBOSE
      std::cout << "INFO: Expected vs. model prediction: ";
#endif
      //hls-fpga-machine-learning insert predictions
      unsigned expected_prediction = argmax_vector<N_LAYER_5>(pr);
#ifdef VERBOSE
      std::cout << expected_prediction << "/";
#endif
      unsigned model_prediction = layer7_out;
#ifdef VERBOSE
      std::cout << model_prediction << std::endl;
#endif
      //hls-fpga-machine-learning insert tb-output
      fout << model_prediction << std::endl;
      if (model_prediction != expected_prediction) errors++;
      outputs++;
    }
    float error_rate = float(errors) * 100 / outputs;
#ifdef VERBOSE
    std::cout << "INFO: Total errors: " << errors << " (" << outputs << ")" << std::endl;
    std::cout << "INFO: Error rate: " << error_rate << " %" << std::endl;
#endif
    std::cout << "INFO: Accuracy: " << 100 - error_rate << " %" << std::endl;

    fin.close();
    fpr.close();
  } else {
    std::cout << "INFO: Unable to open input/predictions file, using default input." << std::endl;

    //hls-fpga-machine-learning insert zero
    input_t input_1[N_INPUT_1_1];
    nnet::fill_zero<input_t, N_INPUT_1_1>(input_1);
    result_t layer7_out;

    //hls-fpga-machine-learning insert top-level-function
    myproject(input_1,layer7_out
#if defined(V03)
              , w2, b2, w5, b5
#endif
            );

    //hls-fpga-machine-learning insert output
    //nnet::print_result<result_t, N_LAYER_5>(layer7_out, std::cout, true);
    std::cout << layer7_out << std::endl;

    //hls-fpga-machine-learning insert tb-output
    fout << layer7_out << std::endl;

    //nnet::print_result<result_t, N_LAYER_5>(layer7_out, fout);

  }

  fout.close();
  std::cout << "INFO: Saved inference results to file: " << RESULTS_LOG << std::endl;
  std::cout << "INFO: Design d64 done!" << std::endl;

  return 0;
}
