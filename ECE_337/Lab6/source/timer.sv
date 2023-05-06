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
    output logic shift_strobe, packet_done
);
    flex_counter CNT10CLKL
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | packet_done),
        .count_enable( enable_timer ),
        .rollover_val( 4'd10 ),
        .count_out( ),
        .rollover_flag( shift_strobe ) 
    );

    flex_counter CNT9BITS
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | packet_done),
        .count_enable( shift_strobe ),
        .rollover_val( 4'd9 ),
        .count_out( ),
        .rollover_flag( packet_done ) 
    );
endmodule