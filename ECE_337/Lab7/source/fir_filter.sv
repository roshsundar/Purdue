// $Id: $
// File name:   fir_filter.sv
// Created:     2/28/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Performs  2-point High-Pass FIR Filter.

module fir_filter
(
    input logic clk, n_reset,
    input logic [15:0] sample_data, fir_coefficient,
    input logic load_coeff, data_ready,
    output logic one_k_samples, modwait,
    output logic [15:0] fir_out,
    output logic err
);
    logic dr;
    logic lc;
    logic overflow;
    logic cnt_up;
    logic clear;
    logic [2:0] op;
    logic [3:0] src1;
    logic [3:0] src2;
    logic [3:0] dest;
    logic [16:0] outreg_data;

    sync_low SYNC_DR (.clk(clk), .n_rst(n_reset), .async_in(data_ready), .sync_out(dr));

    sync_low SYNC_LC (.clk(clk), .n_rst(n_reset), .async_in(load_coeff), .sync_out(lc));

    controller CONT (.clk(clk), .n_rst(n_reset), .dr(dr), .lc(lc), .overflow(overflow), .cnt_up(cnt_up), .clear(clear), .modwait(modwait), .op(op), .src1(src1), .src2(src2), .dest(dest), .err(err));

    counter CNT1000 (.clk(clk), .n_rst(n_reset), .cnt_up(cnt_up), .clear(clear), .one_k_samples(one_k_samples));

    datapath DPATH (.clk(clk), .n_reset(n_reset), .op(op), .src1(src1), .src2(src2), .dest(dest), .ext_data1(sample_data), .ext_data2(fir_coefficient), .outreg_data(outreg_data), .overflow(overflow));

    magnitude MAG (.in(outreg_data), .out(fir_out));
endmodule