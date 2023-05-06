module counter(input logic clk, input logic n_rst, input logic cnt_up, input logic clear, 
                output logic bit_strobe, output logic bit_finished, output logic eop_finished, 
                output logic load_enable);
  
    logic [3:0] check;
    logic [4:0] count1;
    logic [3:0] count2;
    
    //simple combinational block that set roll over value to 8 or 9 depending on bit_strobe
    // logic [3:0] flip_bit;
    // always_comb begin 
    //     flip_bit = 5'd8;
    //     if(bit_strobe == 1'b1) begin 
    //         flip_bit = 5'd9;
    //     end else begin 
    //         flip_bit = 5'd8;
    //     end
    // end

    //this will count for 8 bit periods
    //will output a bit_finished that indicates 8bit period is done, trigger fsm to go next state
    txtwentyfive_counter #(.NUM_CNT_BITS(5)) clk_count (.clk(clk), .n_rst(n_rst), .clear(clear), .count_enable(cnt_up), .rollover_val(5'd25), .count_out(count1), .rollover_flag(bit_strobe));
    txflex_counter #(.BIT_WIDTH(4)) bit_count (.clk(clk), .n_rst(n_rst), .clear(clear), .count_enable(bit_strobe),.rollover_val(4'd8), .count_out(count2), .rollover_flag(bit_finished));
    
    assign load_enable = (count1 == 4) && (count2 == 0);
    //this will count for 2 bit periods for eop 
    //will output a eop_finished that triggers the fsm to go different state 
    txflex_counter #(.BIT_WIDTH(4)) eop_count (.clk(clk), .n_rst(n_rst), .clear(clear), .count_enable(bit_strobe), .rollover_val(4'd1), .count_out(), .rollover_flag(eop_finished));



endmodule
