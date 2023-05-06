// $Id: $
// File name:   timer.sv
// Created:     2/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: control the shift register to shift in 9 bits

module timer
(
    input logic clk, n_rst, enable_timer,
    input logic [3:0] data_size,
    input logic [13:0] bit_period,
    output logic shift_strobe, packet_done
);
    flex_counter #(.NUM_CNT_BITS(14)) CNTCLK
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | packet_done),
        .count_enable( enable_timer ),
        .rollover_val(bit_period),
        .count_out( ),
        .rollover_flag( shift_strobe ) 
    );

    flex_counter CNTBITS
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | packet_done),
        .count_enable( shift_strobe ),
        .rollover_val(data_size + 4'b0001),
        .count_out( ),
        .rollover_flag( packet_done ) 
    );
endmodule