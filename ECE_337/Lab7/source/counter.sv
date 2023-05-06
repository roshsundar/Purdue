// $Id: $
// File name:   counter.sv
// Created:     2/28/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: counts how many samples have been processed & asserts high after 1000
module counter
(
    input logic clk, n_rst, cnt_up, clear,
    output logic one_k_samples
);
    flex_counter #(.NUM_CNT_BITS(10)) CNT1000 (.clk(clk), .n_rst(n_rst), .clear(clear), .count_enable(cnt_up), .rollover_val(10'd1000), .count_out(), .rollover_flag(one_k_samples));
endmodule