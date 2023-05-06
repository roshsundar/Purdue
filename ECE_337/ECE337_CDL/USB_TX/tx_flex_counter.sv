module txflex_counter 
    #(
        parameter BIT_WIDTH = 4
    ) 

    (
    input logic clk, 
    input logic n_rst, 
    input logic clear, 
    input logic count_enable, 
    input logic [(BIT_WIDTH - 1):0] rollover_val,
    output logic [(BIT_WIDTH - 1):0] count_out, 
    output logic rollover_flag
    );

    logic [(BIT_WIDTH - 1):0] temp_count;
    logic temp_rollover;

    always_comb begin 
        temp_count = count_out;
        temp_rollover = rollover_flag;
        
        if (clear == 1) begin 
            temp_count = 0;
            temp_rollover = 0;
        end 
        else if (count_enable) begin 
                if(count_out == rollover_val) begin 
                    temp_count = 1;
                    temp_rollover = 0;
                end
                else if ((count_out + 1) == rollover_val) begin 
                    temp_count = count_out + 1;
                    temp_rollover = 1;
                end
                else begin 
                    temp_count = count_out + 1;
                    temp_rollover = 0;
                end
            end
    end     
    
    always_ff @(posedge clk, negedge n_rst) begin 
        if(n_rst == 0) begin 
            count_out <= 0;
            rollover_flag <= 0;
        end
        else begin 
            count_out <= temp_count;
            rollover_flag <= temp_rollover;
        end
    end

endmodule
