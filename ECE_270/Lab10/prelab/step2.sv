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

  logic [2:0] q;
  logic [2:0] next_q;
  
  always_ff @(posedge pb[1], posedge pb[0])
  begin
    if (pb[1] == 1'b1)
    begin
      q <= 3'b010;
    end
    else
    begin
      q <= next_q;
    end
  end
  
  logic [7:0] p;
  hc138 decode(.a(q), .e1(0), .e2(0), .e3(1), .y(p));
  assign next_q[0] = ~ (p[0] & p[1] & p[6] & p[7]);
  assign next_q[1] = ~ (p[4] & p[5] & p[6] & p[7]);
  assign next_q[2] = ~ (p[1] & p[2] & p[4] & p[6]);
  assign right[2:0] = q;
  assign left[2:0] = next_q;
  
endmodule

// A SystemVerilog implementation of the 74HC138
// 3-to-8 decoder with active-low outputs.
module hc138(input logic e1,e2,e3,
             input logic [2:0]a,
             output [7:0]y);

  logic enable;
  logic [7:0] ypos;  // uninverted y
  assign enable = ~e1 & ~e2 & e3;
  assign ypos = { enable &  a[2] &  a[1] &  a[0],
                  enable &  a[2] &  a[1] & ~a[0],
                  enable &  a[2] & ~a[1] &  a[0],
                  enable &  a[2] & ~a[1] & ~a[0],
                  enable & ~a[2] &  a[1] &  a[0],
                  enable & ~a[2] &  a[1] & ~a[0],
                  enable & ~a[2] & ~a[1] &  a[0],
                  enable & ~a[2] & ~a[1] & ~a[0] };
  assign y = ~ypos;
endmodule