// $Id: $
// File name:   flex_pts_sr.sv
// Created:     2/10/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Flexible and Scalable Parallel-to-Serial Shift Register Design
module flex_pts_sr
#(
	NUM_BITS = 4,
  	SHIFT_MSB = 1
)
(
    input logic clk, n_rst, shift_enable, load_enable,
    input logic [(NUM_BITS-1):0] parallel_in,
    output logic serial_out 
);
    logic [(NUM_BITS-1):0] nxt_parallel;
     logic [(NUM_BITS-1):0] parallel_vals;

    always_comb begin
        if (load_enable) begin
            nxt_parallel = parallel_in;
        end
        else if (shift_enable) begin
            if (SHIFT_MSB == 1) 
				nxt_parallel = {parallel_vals[(NUM_BITS-2):0], 1'b1};
			else
				nxt_parallel = {1'b1, parallel_vals[(NUM_BITS-1):1]};
        end
        else
            nxt_parallel = parallel_vals;
    end

    always_ff @ (posedge clk, negedge n_rst) begin
		if (n_rst == 1'b0) begin
			parallel_vals <= '1;
		end		
		else begin
			parallel_vals <= nxt_parallel;
		end
	end

    assign serial_out = SHIFT_MSB ? (parallel_vals[(NUM_BITS-1)]) : (parallel_vals[0]);

endmodule