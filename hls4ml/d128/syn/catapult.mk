help:
	@echo "make <TAB> for usage"
.PHONY: help

CCS := $(shell ls -t Catapult*ccs 2> /dev/null | head -n1)

gui:
	catapult $(CCS) &
.PHONY: gui

hls-gui: --init
	catapult -file build_prj_top.tcl -logfile ./catapult-gui.log
#tar cvfz hls-$$(date '+%Y%m%d-%H%M%S').tgz Catapult.ccs  Catapult hls-gui.log tb_data/catapult_asic_csim_results.log tb_data/catapult_asic_rtl_cosim_results.log
.PHONY: hls-gui

hls-sh: --init
	time catapult -shell -file build_prj_top.tcl -logfile ./catapult.log
#tar cvfz catapult-asic-$$(date '+%Y%m%d-%H%M%S').tgz Catapult_asic.ccs  Catapult_asic catapult-asic.log tb_data/catapult_asic_csim_results.log tb_data/catapult_asic_rtl_cosim_results.log
.PHONY: hls-sh

kill-all:
	pkill -f catapult || pkill -f vsim
.PHONY: kill-all

clean:
	@echo "INFO: make ultraclean"
.PHONY: clean

ultraclean:
	rm -rf Catapult*
	rm -f Catapult*.ccs
	rm -f catapult*.log
	rm -f tb_data/*.log
.PHONY: ultraclean
