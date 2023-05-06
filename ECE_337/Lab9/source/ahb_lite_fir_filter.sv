// $Id: $
// File name:   ahb_lite_fir_filter.sv
// Created:     3/27/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: This is the full design module that connects the dedicated AHB-Lite-Slave interface and FIR Filter modules together
// to form the overall SoC accelerator module.

module ahb_lite_fir_filter(
    input logic clk, n_rst,
    input logic hsel, hsize, hwrite,
    input logic [3:0] haddr,
    input logic [1:0] htrans,
    input logic [15:0] hwdata,
    output logic [15:0] hrdata,
    output logic hresp
);
    logic [15:0] sample_data, fir_coefficient, fir_out;
    logic [1:0] coefficient_num;
    logic data_ready, new_coefficient_set, modwait, err, load_coeff;

    ahb_lite_slave AHBLITE 
    (
        .clk(clk), .n_rst(n_rst), .sample_data(sample_data), .data_ready(data_ready), .new_coefficient_set(new_coefficient_set), 
        .coefficient_num(coefficient_num), .fir_coefficient(fir_coefficient), .modwait(modwait), .fir_out(fir_out), .err(err), 
        .hsel(hsel), .haddr(haddr), .hsize(hsize), .htrans(htrans), .hwrite(hwrite), .hwdata(hwdata), .hrdata(hrdata), .hresp(hresp)
    );

    coefficient_loader LOAD
    (
        .clk(clk), .n_reset(n_rst), .new_coefficient_set(new_coefficient_set), .modwait(modwait), .load_coeff(load_coeff), .coefficient_num(coefficient_num)
    );

    fir_filter FIR
    (
        .clk(clk), .n_reset(n_rst), .sample_data(sample_data), .data_ready(data_ready), .fir_coefficient(fir_coefficient), .load_coeff(load_coeff), 
        .one_k_samples(), .modwait(modwait), .fir_out(fir_out), .err(err)
    );

endmodule