// $Id: $
// File name:   sr_9bit.sv
// Created:     2/16/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: 9-bit Shift Register that will shift the serial data received

module sr_9bit (
    input clk, n_rst, shift_strobe, serial_in,
    output [7:0] packet_data,
    output stop_bit
);
    logic [8:0] shift_o;

    flex_stp_sr #(.NUM_BITS(9), .SHIFT_MSB(0)) ShiftReg (
        .clk(clk), 
        .n_rst(n_rst), 
        .serial_in(serial_in), 
        .shift_enable(shift_strobe), 
        .parallel_out(shift_o)
    );

    assign stop_bit = shift_o[8];
    assign packet_data = shift_o[7:0];
endmodule