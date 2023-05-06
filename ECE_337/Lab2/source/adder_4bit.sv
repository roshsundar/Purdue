// $Id: $
// File name:   adder_4bit.sv
// Created:     1/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description:  4-Bit Ripple Carry Adder implemeted with structural verilog
module adder_4bit
(
    input logic [3:0] a,
    input logic [3:0] b,
    input logic carry_in,
    output logic [3:0] sum,
    output logic overflow
);
    logic [4:0] carrys;
    genvar i;
    assign carrys[0] = carry_in;

    generate
        for (i = 0; i <= 3; i = i + 1) begin
            adder_1bit IX (.a(a[i]), .b(b[i]), .carry_in(carrys[i]), .sum(sum[i]), .carry_out(carrys[i+1]));
        end
    endgenerate

    assign overflow = carrys[4];
endmodule