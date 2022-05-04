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
  prienc16to4 u1(.in(pb[15:0]), .out(right[3:0]), .strobe(green));
  
endmodule


module prienc16to4 (
  input logic [15:0] in,
  output logic [3:0] out,
  output logic strobe
);
  
  assign {out,strobe} = in[15] == 1 ? 5'b11111 /* Input E is high */ :
                        in[14] == 1 ? 5'b11101 /* Input E is high */ :
                        in[13] == 1 ? 5'b11011 /* Input D is high */ :
                        in[12] == 1 ? 5'b11001 /* Input C is high */ :
                        in[11] == 1 ? 5'b10111 /* Input B is high */ :
                        in[10] == 1 ? 5'b10101 /* Input A is high */ :
                        in[9] == 1 ? 5'b10011 /* Input 9 is high */ :
                        in[8] == 1 ? 5'b10001 /* Input 8 is high */ :
                        in[7] == 1 ? 5'b01111 /* Input 7 is high */ :
                        in[6] == 1 ? 5'b01101 /* Input 6 is high */ :
                        in[5] == 1 ? 5'b01011 /* Input 5 is high */ :
                        in[4] == 1 ? 5'b01001 /* Input 4 is high */ :
                        in[3] == 1 ? 5'b00111 /* Input 3 is high */ :
                        in[2] == 1 ? 5'b00101 /* Input 2 is high */ :
                        in[1] == 1 ? 5'b00011 /* Input 1 is high */ :
                        in[0] == 1 ? 5'b00001 /* Input 0 is high */ :
                                     5'b00000; // Nothing pressed.
endmodule