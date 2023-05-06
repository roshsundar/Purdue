// $Id: $
// File name:   sr_8bit.sv
// Created:     2/16/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: 9-bit Shift Register that will shift the serial data received

module sr_8bit (
    input logic clk, n_rst, shift_strobe, serial_in,
    output logic [7:0] rcv_byte
);

    flex_stp_sr #(.NUM_BITS(8), .SHIFT_MSB(0)) ShiftReg (
        .clk(clk), 
        .n_rst(n_rst), 
        .serial_in(serial_in), 
        .shift_enable(shift_strobe), 
        .parallel_out(rcv_byte)
    );

endmodule