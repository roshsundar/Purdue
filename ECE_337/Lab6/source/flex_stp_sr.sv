// $Id: $
// File name:   flex_stp_sr.sv
// Created:     2/10/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Flexible and Scalable Serial-to-Parallel Shift Register Design

module flex_stp_sr
#(
	NUM_BITS = 4,
  	SHIFT_MSB = 1
)

(
	input logic clk, n_rst, shift_enable,serial_in,
	output logic [(NUM_BITS-1):0] parallel_out	
);
	logic [NUM_BITS-1:0] nxt_out;	
	
	always_comb begin
		if (shift_enable == 1'b1) begin
			if (SHIFT_MSB == 1) 
				nxt_out = {parallel_out[(NUM_BITS-2):0], serial_in};
			else
				nxt_out = {serial_in, parallel_out[(NUM_BITS-1):1]};
			end
		else begin
			nxt_out = parallel_out; 	
		end
	end

    always_ff @ (posedge clk, negedge n_rst) begin
		if (n_rst == 1'b0) begin
			parallel_out <= '1;
		end		
		else begin
			parallel_out <= nxt_out;
		end
	end

endmodule
			