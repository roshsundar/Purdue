// $Id: $
// File name:   magnitude.sv
// Created:     2/28/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: takes in 17-bit signed input and converts to 16-bit unsigned output

module magnitude
(
    input logic [16:0] in,
    output logic [15:0] out
);
    always_comb begin
        if (in[16] == 0)
            out = in[15:0];
        else
            out = ~in[15:0] + 1'b1;
    end
endmodule