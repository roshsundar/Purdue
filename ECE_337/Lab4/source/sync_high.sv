// $Id: $
// File name:   sync_low
// Created:     2/1/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: 2 flip-flop synchonizer with reset to high
module sync_high
(
    input logic clk,
    input logic n_rst,
    input logic async_in,
    output logic sync_out
);
    logic Q1_D2;

    always_ff @( posedge clk, negedge n_rst ) begin
        if (1'b0 == n_rst) begin
            Q1_D2 <= 1;
            sync_out <= 1;
        end
        else begin
            Q1_D2 <= async_in;
            sync_out <= Q1_D2;
        end
    end

endmodule