// $Id: $
// File name:   edge_detect.sv
// Created:     4/17/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: 1 -> 0 detector

module edge_detect (
    input logic clk, n_rst,
    input logic d_plus_sync,
    output logic d_edge
);

    logic new_sample, old_sample;

    always @ (negedge n_rst, posedge clk) begin
        if(1'b0 == n_rst) begin
            old_sample  <= 1'b1; // Reset value to idle line value
            new_sample  <= 1'b1; // Reset value to idle line value
        end
        else begin
            old_sample  <= new_sample;
            new_sample  <= d_plus_sync;
        end
    end

    // Detect a falling edge -> new sample must be '0' and old sample must be '1'
    assign d_edge = old_sample & (~new_sample); 

endmodule