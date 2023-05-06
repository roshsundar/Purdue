module flex_pts_sr
    #(
        parameter NUM_BITS = 4,
        parameter SHIFT_MSB = 1'b0
    ) 
    (input logic clk, 
    input logic n_rst, 
    input logic shift_enable ,
    input logic load_enable,
    input logic [NUM_BITS - 1: 0] parallel_in,
    output logic serial_out);

    logic temp_out;
    logic [(NUM_BITS - 1) : 0] next_data, parallel_out;

    // first next state logic
    always_comb begin 

        if(load_enable == 1'b1) begin 
            next_data = parallel_in;
        end
        else if(shift_enable == 1) begin 
            if(SHIFT_MSB  == 1) begin 
                next_data = {parallel_out[(NUM_BITS - 2): 0], 1'b1}; 
            end 
 
            else begin 
                next_data = {1'b1, parallel_out[(NUM_BITS - 1): 1]};
            end
        end
        else begin 
            next_data = parallel_out;
        end
    end

    //flip flop 
    always_ff @(posedge clk, negedge n_rst) begin 
        if(n_rst == 0) begin 
            parallel_out <= '1;
        end else begin 
            parallel_out <= next_data;
        end
    end

    //final output logic 
    always_comb begin 
        if(SHIFT_MSB == 1) begin 
            serial_out = parallel_out[NUM_BITS - 1];
        end 
        else begin 
            serial_out = parallel_out[0];
        end 
    end 


endmodule

