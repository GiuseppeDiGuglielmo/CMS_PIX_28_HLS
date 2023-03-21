if {[file isdirectory $project_name]} {
    project load $project_name
} else {
    project new -name $project_name
}

#
# Reset the options to the factory defaults
#

solution new -state initial -version $opt(version) myproject

solution options defaults

#solution options set Flows/ModelSim/VLOG_OPTS {-suppress 12110}
#solution options set Flows/ModelSim/VSIM_OPTS {-t ps -suppress 12110}
#flow package option set /SCVerify/USE_QUESTASIM false
flow package option set /SCVerify/USE_NCSIM true
solution options set Flows/DesignCompiler/OutNetlistFormat verilog
solution options set /Input/CppStandard c++11
#solution options set /Output/OutputVHDL false
#solution options set /TextEditor/FontSize 9
#solution options set /Input/TargetPlatform x86_64
#flow package require /SCVerify
#flow package require /UVM

#if {$opt(asic) > 0} {
#    flow package option set /UVM/UVM_DIR UVM_asic
#} else {
#    flow package option set /UVM/UVM_DIR UVM_fpga
#}

#directive set -DESIGN_GOAL area
##directive set -OLD_SCHED false
#directive set -SPECULATE true
#directive set -MERGEABLE true
directive set -REGISTER_THRESHOLD 245760
#directive set -MEM_MAP_THRESHOLD 32
#directive set -LOGIC_OPT false
#directive set -FSM_ENCODING none
#directive set -FSM_BINARY_ENCODING_THRESHOLD 64
#directive set -REG_MAX_FANOUT 0
#directive set -NO_X_ASSIGNMENTS true
#directive set -SAFE_FSM false
#directive set -REGISTER_SHARING_MAX_WIDTH_DIFFERENCE 8
#directive set -REGISTER_SHARING_LIMIT 0
#directive set -ASSIGN_OVERHEAD 0
#directive set -TIMING_CHECKS true
#directive set -MUXPATH true
#directive set -REALLOC true
#directive set -UNROLL no
#directive set -IO_MODE super
#directive set -CHAN_IO_PROTOCOL standard
#directive set -ARRAY_SIZE 1024
#directive set -REGISTER_IDLE_SIGNAL false
#directive set -IDLE_SIGNAL {}
#directive set -STALL_FLAG false
#directive set -TRANSACTION_DONE_SIGNAL false
#directive set -DONE_FLAG {}
#directive set -READY_FLAG {}
#directive set -START_FLAG {}
#directive set -BLOCK_SYNC none
#directive set -TRANSACTION_SYNC ready
#directive set -DATA_SYNC none
#directive set -CLOCKS {clk {-CLOCK_PERIOD 0.0 -CLOCK_EDGE rising -CLOCK_UNCERTAINTY 0.0 -RESET_SYNC_NAME rst -RESET_ASYNC_NAME arst_n -RESET_KIND sync -RESET_SYNC_ACTIVE high -RESET_ASYNC_ACTIVE low -ENABLE_ACTIVE high}}
#directive set -RESET_CLEARS_ALL_REGS true
#directive set -CLOCK_OVERHEAD 20.000000
#directive set -OPT_CONST_MULTS use_library
#directive set -CHARACTERIZE_ROM false
#directive set -PROTOTYPE_ROM true
#directive set -ROM_THRESHOLD 64
#directive set -CLUSTER_ADDTREE_IN_COUNT_THRESHOLD 0
#directive set -CLUSTER_OPT_CONSTANT_INPUTS true
#directive set -CLUSTER_RTL_SYN false
#directive set -CLUSTER_FAST_MODE false
#directive set -CLUSTER_TYPE combinational
#directive set -COMPGRADE fast

# Design specific options.
solution options set Flows/QuestaSIM/SCCOM_OPTS {-g -x c++ -std=c++11 -Wall -Wno-unused-label -Wno-unknown-pragmas}
switch $opt(version) {
    "v01" {
        solution options set /Input/CompilerFlags {-DV01}
    }
    "v02" {
        solution options set /Input/CompilerFlags {-DV02}
    }
    "v03" {
        solution options set /Input/CompilerFlags {-DV03}
    }
    "v03c" {
        solution options set /Input/CompilerFlags {-DV03}
    }
    default {
        # defaults
    }
}
solution options set /Input/SearchPath {../inc ../src}

# Add source files.
solution file add ../src/firmware/myproject.cpp -type C++
solution file add ../tb/myproject_test.cpp -type C++ -exclude true

#
# Output
#

# Verilog only
solution option set Output/OutputVHDL false
solution option set Output/OutputVerilog true

# Package output in Solution dir
solution option set Output/PackageOutput true
solution option set Output/PackageStaticFiles true

# Add Prefix to library and generated sub-blocks
solution option set Output/PrefixStaticFiles true
solution options set Output/SubBlockNamePrefix "converterBlock_"

# Do not modify names
solution option set Output/DoNotModifyNames true


go new

#
#
#

go analyze

#
#
#

# Set the top module and inline all of the other functions.
#directive set -DESIGN_HIERARCHY myproject
switch $opt(version) {
    "v01" {
        solution design set myproject -top
        solution design set {nnet::relu<ac_fixed<16, 8, true, AC_RND_CONV, AC_SAT>, ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, relu_config4>} -inline
        solution design set {nnet::dense<ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config2>} -inline
        solution design set {nnet::dense<ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, ac_fixed<16, 6, true, AC_TRN, AC_WRAP>, config6>} -inline
    }
    "v02" {
        solution design set myproject -top
        solution design set {nnet::relu<ac_fixed<16, 8, true, AC_RND_CONV, AC_SAT>, ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, relu_config4>} -inline
        solution design set {nnet::dense<ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config2>} -inline
        solution design set {nnet::dense<ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, ac_fixed<16, 6, true, AC_TRN, AC_WRAP>, config6>} -inline
    }
    "v03" {
        solution design set myproject -top
        solution design set {nnet::dense<ac_int<6, false>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config2>} -inline
        solution design set {nnet::relu<ac_fixed<16, 8, true, AC_RND_CONV, AC_SAT>, ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, relu_config4>} -inline
        solution design set {nnet::dense<ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config6>} -inline
    }
    "v03c" {
        solution design set myproject -ccore
        solution design set myproject -combinational
        solution design set ac::fx_div<8> -inline
        solution design set {nnet::dense<ac_int<6, false>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config2>} -inline
        solution design set {nnet::relu<ac_fixed<16, 8, true, AC_RND_CONV, AC_SAT>, ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, relu_config4>} -inline
        solution design set {nnet::dense<ac_fixed<10, 0, false, AC_RND_CONV, AC_SAT>, ac_fixed<16, 8, true, AC_TRN, AC_WRAP>, config6>} -inline
    }
    default {
        # defaults
    }
}

go compile

# Run C simulation.
if {$opt(csim)} {
    flow run /SCVerify/launch_make ./scverify/Verify_orig_cxx_osci.mk {} SIMTOOL=osci sim
}

#
#
#

# Run HLS.
if {$opt(hsynth)} {

    if {$opt(asic) == 0} {
        solution library add nangate-45nm_beh -- -rtlsyntool DesignCompiler -vendor Nangate -technology 045nm
        solution library add ccs_sample_mem
    } elseif {$opt(asic) == 1} {
        solution library add nangate-45nm_beh -- -rtlsyntool RTLCompiler -vendor Nangate -technology 045nm
        solution library add ccs_sample_mem
    } elseif {$opt(asic) == 2} {
        puts "ERROR: Cadence Genus is not supported"
        exit 1
    } elseif {$opt(asic) == 3} {
        solution library add nangate-45nm_beh -- -rtlsyntool OasysRTL -vendor Nangate -technology 045nm
        solution library add ccs_sample_mem
    } else {
        puts "ERROR: Unspecified backend flow"
        exit 1
    }


    go libraries

    #
    #
    #

    directive set -CLOCKS { \
        clk { \
            -CLOCK_PERIOD 25.0 \
            -CLOCK_EDGE rising \
            -CLOCK_HIGH_TIME 12.5 \
            -CLOCK_OFFSET 0.000000 \
            -CLOCK_UNCERTAINTY 0.0 \
            -RESET_KIND sync \
            -RESET_SYNC_NAME rst \
            -RESET_SYNC_ACTIVE high \
            -RESET_ASYNC_NAME arst_n \
            -RESET_ASYNC_ACTIVE low \
            -ENABLE_NAME {} \
            -ENABLE_ACTIVE high \
        } \
    }

    switch $opt(version) {
        "v01" {
            directive set /myproject -MAP_TO_MODULE {}
        }
        "v02" {
            directive set /myproject -MAP_TO_MODULE {}
        }
        "v03" {
            directive set /myproject -MAP_TO_MODULE {}
        }
        "v03c" {
            #directive set /myproject -MAP_TO_MODULE {}
        }
        default {
            # defaults
        }
    }

    # BUGFIX: This prevents the creation of the empty module CGHpart. In the
    # next releases of Catapult HLS, this may be fixed.
    directive set /myproject -GATE_EFFORT normal
    directive set /myproject -GATE_REGISTERS false

    go assembly

    # Top-Module I/O
    switch $opt(version) {
        "v01" {
            directive set /myproject/input_1:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/layer7_out:rsc -MAP_TO_MODULE ccs_ioport.ccs_out
        }
        "v02" {
            directive set /myproject/input_1:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/layer7_out:rsc -MAP_TO_MODULE ccs_ioport.ccs_out
        }
        "v03" {
            directive set /myproject/input_1:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/layer7_out:rsc -MAP_TO_MODULE ccs_ioport.ccs_out
            directive set /myproject/w2:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/b2:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/w5:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
            directive set /myproject/b5:rsc -MAP_TO_MODULE ccs_ioport.ccs_in
        }
        "v03c" {
            #
        }
        default {
            # defaults
        }
    }

    # Sub-modules
    switch $opt(version) {
        "v01" {
            # defaults
        }
        "v02" {
            # defaults
        }
        "v03" {
            # defaults
        }
        "v03c" {
            # defaults
        }
        default {
            # defaults
        }
    }

    # Clusters
    switch $opt(version) {
        "v01" {
            # defaults
        }
        "v02" {
            # defaults
        }
        "v03" {
            # defaults
        }
        "v03c" {
            # defaults
        }
        default {
            # defaults
        }
    }

    # Arrays
    switch $opt(version) {
        "v01" {
            directive set /myproject/w2.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/w5.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/nnet::dense_latency<input_t,layer2_t,config2>:acc.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/nnet::dense_latency<layer4_t,result_t,config6>:acc.rom:rsc -MAP_TO_MODULE {[Register]}

            directive set /myproject/core/layer2_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer3_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer4_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:acc:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,result_t,config6>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,result_t,config6>:acc:rsc -MAP_TO_MODULE {[Register]}
        }
        "v02" {
            directive set /myproject/w2.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/w5.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/nnet::dense_latency<input_t,layer2_t,config2>:acc.rom:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/nnet::dense_latency<layer4_t,result_t,config6>:acc.rom:rsc -MAP_TO_MODULE {[Register]}

            directive set /myproject/core/layer2_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer3_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer4_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:acc:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,result_t,config6>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,result_t,config6>:acc:rsc -MAP_TO_MODULE {[Register]}
        }
        "v03" {
            directive set /myproject/core/layer2_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer3_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/layer4_out:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<input_t,layer2_t,config2>:acc:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,layer6_t,config6>:mult:rsc -MAP_TO_MODULE {[Register]}
            directive set /myproject/core/nnet::dense_latency<layer4_t,layer6_t,config6>:acc:rsc -MAP_TO_MODULE {[Register]}
        }
        "v03c" {
            #
        }
        default {
            # defaults
        }
    }

    # Loops
    #directive set /myproject/core/main -PIPELINE_INIT_INTERVAL 1
    switch $opt(version) {
        "v01" {
            directive set /myproject/core/Product1 -UNROLL no
            directive set /myproject/core/Product2 -UNROLL no
            directive set /myproject/core/Accum1 -UNROLL no
            directive set /myproject/core/Accum2 -UNROLL no
            directive set /myproject/core/Result -UNROLL no
            directive set /myproject/core/nnet::linear<layer2_t,layer3_t,linear_config3>:for -UNROLL no
            directive set /myproject/core/nnet::relu<layer3_t,layer4_t,relu_config4>:for -UNROLL no
            directive set /myproject/core/Product1#1 -UNROLL no
            directive set /myproject/core/Product2#1 -UNROLL no
            directive set /myproject/core/Accum1#1 -UNROLL no
            directive set /myproject/core/Accum2#1 -UNROLL no
            directive set /myproject/core/Result#1 -UNROLL no
        }
        "v02" {
            directive set /myproject/core/Product1 -UNROLL yes
            directive set /myproject/core/Product2 -UNROLL yes
            directive set /myproject/core/Accum1 -UNROLL yes
            directive set /myproject/core/Accum2 -UNROLL yes
            directive set /myproject/core/Result -UNROLL yes
            directive set /myproject/core/nnet::linear<layer2_t,layer3_t,linear_config3>:for -UNROLL yes
            directive set /myproject/core/nnet::linear<layer2_t,layer3_t,linear_config3>:for -PIPELINE_INIT_INTERVAL 0
            directive set /myproject/core/nnet::relu<layer3_t,layer4_t,relu_config4>:for -UNROLL yes
            directive set /myproject/core/Product1#1 -UNROLL yes
            directive set /myproject/core/Product2#1 -UNROLL yes
            directive set /myproject/core/Accum1#1 -UNROLL yes
            directive set /myproject/core/Accum2#1 -UNROLL yes
            directive set /myproject/core/Result#1 -UNROLL yes

            directive set /myproject/core/main -PIPELINE_INIT_INTERVAL 1
        }
        "v03" {
            directive set /myproject/core/Product1 -UNROLL yes
            directive set /myproject/core/Product2 -UNROLL yes
            directive set /myproject/core/ResetAccum -UNROLL yes
            directive set /myproject/core/Accum1 -UNROLL yes
            directive set /myproject/core/Accum2 -UNROLL yes
            directive set /myproject/core/Result -UNROLL yes
            directive set /myproject/core/nnet::linear<layer2_t,layer3_t,linear_config3>:for -UNROLL yes
            directive set /myproject/core/nnet::linear<layer2_t,layer3_t,linear_config3>:for -PIPELINE_INIT_INTERVAL 0
            directive set /myproject/core/nnet::relu<layer3_t,layer4_t,relu_config4>:for -UNROLL yes
            directive set /myproject/core/Product1#1 -UNROLL yes
            directive set /myproject/core/Product2#1 -UNROLL yes
            directive set /myproject/core/ResetAccum#1 -UNROLL yes
            directive set /myproject/core/Accum1#1 -UNROLL yes
            directive set /myproject/core/Accum2#1 -UNROLL yes
            directive set /myproject/core/Result#1 -UNROLL yes

            directive set /myproject/core/main -PIPELINE_INIT_INTERVAL 1
        }
        "v03c" {
            directive set /myproject/core/main -ITERATIONS 1
            directive set /myproject/core/main -PIPELINE_INIT_INTERVAL 0
            directive set /myproject/core/main -UNROLL no
        }
        default {
            # defaults
        }
    }

    if {! $opt(debug)} {

        go architect

        #
        #
        #


        go allocate

        #
        # RTL
        #


        directive set -ENABLE_PHYSICAL true

        go extract

        #
        #
        #

   if {$opt(rtlsim)} {
       flow run /SCVerify/launch_make ./scverify/Verify_rtl_v_msim.mk {} SIMTOOL=msim sim
       #flow run /SCVerify/launch_make ./scverify/Verify_rtl_v_msim.mk {} SIMTOOL=msim simgui

       if {$opt(validation)} {
         puts "***** C/RTL VALIDATION *****"
         if {[compare_files $CSIM_RESULTS $RTL_COSIM_RESULTS]} {
             puts "INFO: Test PASSED"
         } else {
             puts "ERROR: Test failed"
             puts "ERROR: - csim log:      $CSIM_RESULTS"
             puts "ERROR: - RTL-cosim log: $RTL_COSIM_RESULTS"
             exit 1
         }
       }
   }

   if {$opt(lsynth)} {

       if {$opt(asic) == 1} {
           flow run /DesignCompiler/dc_shell ./concat_myproject.v.dc v
       } elseif {$opt(asic) == 2} {
           flow run /RTLCompiler/rc ./concat_myproject.v.rc v
       } elseif {$opt(asic) == 3} {
           flow run /OasysRTL/launch_tool ./concat_myproject.v.or v
       } else {
           flow run /Vivado/synthesize -shell vivado_concat_v/concat_rtl.v.xv
       }

   }


    }
}
#
##flow run /UVM
#
project save
