# Design points

- `v01` hls4ml implementation, all of the loops are rolled, maximum latency, hardcoded weights, I/O over wires.
- `v02` hls4ml implementation, all of the loops are unrollend, latency=1, II=1, hardcoded weights, I/O over wires.
- `v03` hls4ml implementation, all of the loops are unrollend, latency=1, II=1, programmable weights, I/O over wires.
- `v03b` :medal_sports: **hls4ml implementation, all of the loops are unrollend, latency=1, II=1, programmable weights, I/O over wires. Reduced-size layers (64). 6bx16 in and 2bx1 out**
- `v04` Custom implementation, all of the loops are unrollend, latency=1, II=1, programmable weights, I/O over wires.

