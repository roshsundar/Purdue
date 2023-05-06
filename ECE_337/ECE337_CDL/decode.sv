// $Id: $
// File name:   decode.sv
// Created:     4/17/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Decodes NRZ encoded data

module decode (
    input logic clk, n_rst,
    input logic d_plus_sync, shift_en, eop,
    output logic d_orig
);

    logic nxt_old, old_sample;

    always @ (negedge n_rst, posedge clk) begin
        if(1'b0 == n_rst) begin
            old_sample <= d_plus_sync; // Reset value to idle line value
        end
        else begin
            old_sample  <= nxt_old;
        end
    end

    always_comb begin
        if (shift_en) begin
            nxt_old = d_plus_sync;
        end
        else
            nxt_old = old_sample;

        d_orig = ~(d_plus_sync ^ old_sample);
    end
endmodule