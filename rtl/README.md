# Design points

See also this [result summary](https://fermicloud-my.sharepoint.com/:x:/g/personal/gdg_services_fnal_gov/EdJUmntd_xJAkSvxnQh-RBYBDfEPNP56Mq_f-1LgF-4rDQ?e=aIci9G).

||design|latency|II|inputs|outputs|hidden neurons|weights|activations|workspace|notes|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---|
||`v01`|-|-|||||||I/O wires, hardcoded weights, no unrolling|
||`v02`|1|1|||||||I/O wires, hardcoded weights|
||`v03`|1|1|||||||I/O wires, programmable weights|
|:medal_sports:|`v03b`|1|1|16x6b (96)|1x2b (2)|64|5b (6,415) |16b|d64w5a16|I/O wires, programmable weights|
||`v03c`|1|1|16x6b (96)|1x2b (2)|60|5b (6,015)|16b|d60w5a16|I/O wires, programmable weights|
||`v03d`|1|1|16x6b (96)|1x2b (2)|58|5b (5,815)|16b|d58w5a16|I/O wires, programmable weights|
||`v03e`|1|1|16x6b (96)|1x2b (2)|64|5b (6,415) |10b|d64w5a10|I/O wires, programmable weights|
||`v03f`|1|1|16x6b (96)|1x2b (2)|60|5b (6,015)|10b|d60w5a10|I/O wires, programmable weights|
||`v03g`|1|1|16x6b (96)|1x2b (2)|58|5b (5,815)|10b|d58w5a10|I/O wires, programmable weights|
||`v03h`|1|1|16x6b (96)|1x2b (2)|64|4b (5,132)|8b|d64w4a8|I/O wires, programmable weights|
||`v03i`|1|1|16x6b (96)|1x2b (2)|60|4b (4,812)|8b|d60w4a8|I/O wires, programmable weights|
||`v03l`|1|1|16x6b (96)|1x2b (2)|58|4b (4,652)|8b|d58w4a8|I/O wires, programmable weights|
||`v03bc`|1|1|16x6b (96)|1x2b (2)|64|5b (6,415) |16b|d64w5a16|I/O wires, programmable weights, combinational|
||`v03cc`|1|1|16x6b (96)|1x2b (2)|60|5b (6,015)|16b|d60w5a16|I/O wires, programmable weights, combinational|
||`v03dc`|1|1|16x6b (96)|1x2b (2)|58|5b (5,815)|16b|d58w5a16|I/O wires, programmable weights, combinational|
||`v03ec`|1|1|16x6b (96)|1x2b (2)|64|5b (6,415) |10b|d64w5a10|I/O wires, programmable weights, combinational|
||`v03fc`|1|1|16x6b (96)|1x2b (2)|60|5b (6,015)|10b|d60w5a10|I/O wires, programmable weights, combinational|
||`v03gc`|1|1|16x6b (96)|1x2b (2)|58|5b (5,815)|10b|d58w5a10|I/O wires, programmable weights, combinational|
||`v03hc`|1|1|16x6b (96)|1x2b (2)|64|4b (5,132)|8b|d64w4a8|I/O wires, programmable weights, combinational|
||`v03ic`|1|1|16x6b (96)|1x2b (2)|60|4b (4,812)|8b|d60w4a8|I/O wires, programmable weights, combinational|
||`v03lc`|1|1|16x6b (96)|1x2b (2)|58|4b (4,652)|8b|d58w4a8|I/O wires, programmable weights, combinational|
||`v03eca`|1|1|16x6b (96)|1x2b (2)|64|5b (6,415) |10b|d64w5a10|I/O wires, programmable weights, combinational, larger accumulators|
||`v03fca`|1|1|16x6b (96)|1x2b (2)|60|5b (6,015)|10b|d60w5a10|I/O wires, programmable weights, combinational, larger accumulators|
||`v03gca`|1|1|16x6b (96)|1x2b (2)|58|5b (5,815)|10b|d58w5a10|I/O wires, programmable weights, combinational, larger accumulators|
||`v03hca`|1|1|16x6b (96)|1x2b (2)|64|4b (5,132)|8b|d64w4a8|I/O wires, programmable weights, combinational, larger accumulators|
||`v03ica`|1|1|16x6b (96)|1x2b (2)|60|4b (4,812)|8b|d60w4a8|I/O wires, programmable weights, combinational, larger accumulators|
||`v03lca`|1|1|16x6b (96)|1x2b (2)|58|4b (4,652)|8b|d58w4a8|I/O wires, programmable weights, combinational, larger accumulators|
|:arrow_right:|`v03lcr`|1|1|16x6b (96)|1x2b (2)|58|4b (4,652)|8b|d58w4a8|I/O wires, programmable weights, combinational, resized accumulators (9,6), (10,4)|
||`v04`|1|1|14x16b (224)|3x16b (48)|128|5b (11,535)|16b|custom|I/O wires, programmable weights|
