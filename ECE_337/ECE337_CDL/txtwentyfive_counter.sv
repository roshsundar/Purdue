module txtwentyfive_counter
#(
	NUM_CNT_BITS = 5
)
(
	input logic clk, n_rst, clear, count_enable,
	input logic [NUM_CNT_BITS-1:0] rollover_val,
	output logic [NUM_CNT_BITS-1:0] count_out,
	output logic rollover_flag
);
    logic [NUM_CNT_BITS-1:0] nxt_count;
    logic nxt_roll_flag;

    always_comb begin
        if (clear == 1) begin
            nxt_count = '0;
            nxt_roll_flag = 0;
        end
        else if (count_enable == 1) begin
            if (count_out == rollover_val) begin
                nxt_count = 1;
                nxt_roll_flag = 0;
            end
            else if (count_out == 7 || count_out == 15 || count_out == 24) begin
                nxt_count = count_out + 1;
                nxt_roll_flag = 1;
            end
            else begin
                nxt_count = count_out + 1;
                nxt_roll_flag = 0;
            end
        end
        else begin
            nxt_count = count_out;
            nxt_roll_flag = rollover_flag;
        end
    end

    always_ff @ (posedge clk, negedge n_rst)
	begin 
		if (n_rst == 0) begin
			count_out <= '0;
			rollover_flag <= '0;	
		end
		else begin
			count_out <= nxt_count;
            rollover_flag <= nxt_roll_flag;
		end		
	end
endmodule
