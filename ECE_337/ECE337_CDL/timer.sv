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
    output logic shift_strobe, byte_rcvd
);
    twentyfive_counter CNT25CLK
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | byte_rcvd),
        .count_enable( enable_timer ),
        .rollover_val( 5'd25 ),
        .count_out( ),
        .rollover_flag( shift_strobe ) 
    );

    flex_counter CNT8BITS
    ( 
        .clk( clk ),
        .n_rst( n_rst ),
        .clear( !enable_timer | byte_rcvd),
        .count_enable( shift_strobe ),
        .rollover_val( 4'd8 ),
        .count_out( ),
        .rollover_flag( byte_rcvd ) 
    );
endmodule