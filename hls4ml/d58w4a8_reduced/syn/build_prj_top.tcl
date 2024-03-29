array set opt {
    # The 'asic' flag specifies if you are targeting ASIC or FPGA:
    # = 0 -> Mentor Design Compiler
    # = 1 -> Cadence Encounter RTL Compiler
    # = 2 -> Cadence Genus
    # = 3 -> Mentor Oasys RTL
    version    "v03c"
    debug      1
    asic       3
    csim       0
    hsynth     1
    rtlsim     0
    validation 0
    lsynth     1
}

set project_name "Catapult_asic"
source ./build_prj.tcl
