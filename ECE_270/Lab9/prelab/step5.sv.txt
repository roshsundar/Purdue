`default_nettype none
// Empty top module

module top (
  // I/O ports
  input  hz100, reset,
  input  [20:0] pb,
  output [7:0] left, right,
         ss7, ss6, ss5, ss4, ss3, ss2, ss1, ss0,
  output red, green, blue,

  // UART ports
  output [7:0] txdata,
  input  [7:0] rxdata,
  output txclk, rxclk,
  input  txready, rxready
);

  // Your code goes here...
  hc74_reset u4 (.c(pb[0]), .d(right[2]), .q(right[3]), .rn(pb[16]));
  hc74_reset u3 (.c(pb[0]), .d(right[1]), .q(right[2]), .rn(pb[16]));
  hc74_reset u2 (.c(pb[0]), .d(right[0]), .q(right[1]), .rn(pb[16]));
  hc74_set u1   (.c(pb[0]), .d(right[3]), .q(right[0]), .sn(pb[16]));
endmodule

// Add more modules down here...

// This is a single D flip-flop with an active-low asynchronous set (preset).
// It has no asynchronous reset because the simulator does not allow it.
// Other than the lack of a reset, it is half of a 74HC74 chip.
module hc74_set(input logic d, c, sn,
                  output logic q, qn);
  assign qn = ~q;
  always_ff @(posedge c, negedge sn)
    if (sn == 1'b0)
      q <= 1'b1;
    else
      q <= d;
endmodule

// This is a single D flip-flop with an active-low asynchronous reset (clear).
// It has no asynchronous set because the simulator does not allow it.
// Other than the lack of a set, it is half of a 74HC74 chip.

module hc74_reset(input logic d, c, rn,
                  output logic q, qn);
  assign qn = ~q;
  always_ff @(posedge c, negedge rn)
    if (rn == 1'b0)
      q <= 1'b0;
    else
      q <= d;
endmodule