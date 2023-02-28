# Design points

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
||`v04`|1|1|14x16b (224)|3x16b (48)|128|5b (11,535)|16b|custom|I/O wires, programmable weights|
