module tx_encoder(input logic clk, input logic n_rst, 
                input logic serial_data, 
                output logic dplus, output logic dminus,
                input logic eop_trigger, input logic shift_strobe);

    logic nextdplus, nextdminus;

    always_ff @(posedge clk, negedge n_rst) begin 
        if(n_rst == 1'b0) begin 
            dplus <= 1;
            dminus <= 0;
        end else begin 
            dplus <= nextdplus;
            dminus <= nextdminus;
        end
    end

    always_comb begin 
        nextdplus = dplus;
        nextdminus = dminus; 
        if(shift_strobe == 1) begin 
            if (eop_trigger == 1'b1) begin //drive both down to zero 
                nextdminus = 0;
                nextdplus = 0;
            end else if(serial_data == 1'b0) begin 
                nextdplus = !dplus;
                nextdminus = !dminus;
            end
        end
    end
        
endmodule