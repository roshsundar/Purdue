`default_nettype none
// Empty top module

module top (
  // I/O ports
  input  logic hz100, reset,
  input  logic [20:0] pb,
  output logic [7:0] left, right,
         ss7, ss6, ss5, ss4, ss3, ss2, ss1, ss0,
  output logic red, green, blue,

  // Ports from/to UART
  output logic [7:0] txdata,
  input  logic [7:0] rxdata,
  output logic txclk, rxclk,
  input  logic txready, rxready
);

  // Your code goes here...
bagraph b(
  .in (pb[15:0]),
  .out ({left[7:0], right[7:0]})
);

decode3to8 d(
  // I/O ports
  .in (pb[2:0]),
  .out ({ss7[7], ss6[7], ss5[7], ss4[7], ss3[7], ss2[7], ss1[7], ss0[7]})
);

endmodule

// Add more modules down here...
module bagraph (
  // I/O ports
  input  logic [15:0] in,
  output logic [15:0] out
);
  // Your code goes here...
assign out[15] = in[15];
assign out[14] = in[14] | in[15];
assign out[13] = in[13] | in[14] | in[15];
assign out[12] = in[12] | in[13] | in[14] | in[15];
assign out[11] = in[11] | in[12] | in[13] | in[14] | in[15];
assign out[10] = in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[9] = in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[8] = in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[7] = in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[6] = in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[5] = in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[4] = in[4] | in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[3] = in[3] | in[4] | in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[2] = in[2] | in[3] | in[4] | in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[1] = in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
assign out[0] = in[0] | in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7] | in[8] | in[9] | in[10] | in[11] | in[12] | in[13] | in[14] | in[15];
  
endmodule

module decode3to8 (
  // I/O ports
  input  logic [2:0] in,
  output logic [7:0] out
);
  // Your code goes here...
assign out[0] = ~in[2]&~in[1]&~in[0];  
assign out[1] = ~in[2]&~in[1]&in[0];   
assign out[2] = ~in[2]&in[1]&~in[0];   
assign out[3] = ~in[2]&in[1]&in[0];   
assign out[4] = in[2]&~in[1]&~in[0];   
assign out[5] = in[2]&~in[1]&in[0];   
assign out[6] = in[2]&in[1]&~in[0];   
assign out[7] = in[2]&in[1]&in[0];   
endmodule