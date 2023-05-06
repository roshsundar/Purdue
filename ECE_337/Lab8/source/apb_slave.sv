// $Id: $
// File name:   apb_slave.sv
// Created:     3/3/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: slave interface device for the APB to drive UART.

module apb_slave
(
    input logic clk, n_rst,
    input logic [7:0] rx_data,
    input logic data_ready, overrun_error, framing_error,
    output logic data_read,
    input logic psel,
    input logic [2:0] paddr,
    input logic penable, pwrite,
    input logic [7:0] pwdata,
    output logic [7:0] prdata,
    output logic pslverr,
    output logic [3:0] data_size,
    output logic [13:0] bit_period
);
    logic nxt_dread;
    logic [7:0] nxt_prdata;
    logic [7:0] rx;
    logic [7:0] dstat;
    logic [7:0] err;
    logic [7:0] nxt_bplow;
    logic [7:0] bp_lower;
    logic [7:0] nxt_bpup;
    logic [7:0] bp_upper;
    logic [7:0] nxt_dsize;

    always_ff @(posedge clk, negedge n_rst) begin
        if (n_rst == 0) begin
            data_read <= 0;
            prdata <= 0;
            rx <= 0;
            //dstat <= '0;
            err <= 0;
            bp_lower <= 8'd10;
            bp_upper <= 0;
            data_size <= 4'd5;
        end
        else begin
            data_read <= nxt_dread;
            prdata <= nxt_prdata;
            rx <= rx_data;
            //dstat <= {7'd0, data_ready};
            if (overrun_error)
                err <= 8'd2;
            else if (framing_error)
                err <= 8'd1;
            else
                err <= 8'd0;
            bp_lower <= nxt_bplow;
            bp_upper <= nxt_bpup;
            data_size <= nxt_dsize;
        end
    end

    assign dstat = data_ready;

    always_comb begin
        pslverr = 0;
        nxt_dread = '0;
        nxt_bplow = bp_lower;
        nxt_bpup = bp_upper;
        nxt_dsize = data_size;
        nxt_prdata = prdata;
        bit_period = {bp_upper, bp_lower};

        if (psel) begin
            if (paddr == 3'h5)
                pslverr = 1;
            else if (pwrite && (paddr == 3'h0 || paddr == 3'h1 || paddr == 3'h6)) begin
                pslverr = 1;
            end
            else if (pwrite == 1) begin
                if (paddr == 3'h2)
                    nxt_bplow = pwdata;
                if (paddr == 3'h3)
                    nxt_bpup = pwdata;
                if (paddr == 3'h4)
                    nxt_dsize = pwdata;
            end
            else if (pwrite == 0) begin
                if (paddr == 3'h0)
                    nxt_prdata = dstat;
                if (paddr == 3'h1)
                    nxt_prdata = err;
                if (paddr == 3'h2)
                    nxt_prdata = bp_lower;
                if (paddr == 3'h3)
                    nxt_prdata = bp_upper;
                if (paddr == 3'h4)
                    nxt_prdata = data_size;
                if (paddr == 3'h6) begin
                    nxt_prdata = rx;
                    nxt_dread = 1;
                end
            end
        end
    end
endmodule