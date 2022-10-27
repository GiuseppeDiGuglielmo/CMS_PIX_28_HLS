#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "myproject.h"
#include "nnet_helpers.h"

#include <mc_scverify.h>

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

#include "w2.h"
#include "b2.h"
#include "w5.h"
#include "b5.h"

CCS_MAIN(int argc, char *argv[])
{
    std::ifstream fin("tb_data/tb_input_features.dat");
    std::ifstream fpr("tb_data/tb_output_predictions.dat");

    std::string RESULTS_LOG = "tb_data/csim_results.log";
    std::ofstream fout(RESULTS_LOG);

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
            result_t layer6_out[N_LAYER_5];

            //hls-fpga-machine-learning insert top-level-function
            unsigned short size_in1,size_out1;
            myproject(input_1,layer6_out,w2,b2,w5,b5);

            std::cout << "INFO: Expected prediction: ";
            //hls-fpga-machine-learning insert predictions
            unsigned expected_prediction = argmax_vector<N_LAYER_5>(pr);
            std::cout << expected_prediction << " ";
            std::cout << std::endl;
            std::cout << "INFO: Model prediction   : ";
            unsigned model_prediction = argmax<result_t, N_LAYER_5, -31>(layer6_out);
            std::cout << model_prediction << " | ";
            //hls-fpga-machine-learning insert quantized
            nnet::print_result<result_t, N_LAYER_5>(layer6_out, std::cout, true);

            //hls-fpga-machine-learning insert tb-output
            nnet::print_result<result_t, N_LAYER_5>(layer6_out, fout);

            if (model_prediction != expected_prediction) errors++;
            outputs++;
//            break;
        }
        float error_rate = float(errors) * 100 / outputs;
        std::cout << "INFO: Total errors: " << errors << " (" << outputs << ")" << std::endl;
        std::cout << "INFO: Error rate: " << error_rate << "%" << std::endl;
        std::cout << "INFO: Accuracy: " << 100 - error_rate << "%" << std::endl;

        fin.close();
        fpr.close();
    }

    fout.close();
    std::cout << "INFO: Saved inference results to file: " << RESULTS_LOG << std::endl;

    return 0;
}
