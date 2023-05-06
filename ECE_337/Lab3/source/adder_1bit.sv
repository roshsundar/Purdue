// $Id: $
// File name:   adder_1bit.sv
// Created:     1/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: 1-bit Full Adder module
module adder_1bit
(
    input logic a,
    input logic b,
    input logic carry_in,
    output logic sum,
    output logic carry_out
);
    assign sum = carry_in ^ (a ^ b);
    assign carry_out = ((~carry_in) & b & a) | (carry_in & (b | a));

    always @(a, b) begin
        assert ((a == 1'b1) || (a == 1'b0)) 
        else $error("Input 'a' of 1-bit adder is not a digital logic value");

        assert ((b == 1'b1) || (b == 1'b0)) 
        else $error("Input 'b' of 1-bit adder is not a digital logic value");
    end
endmodule