module tx_controller (input logic clk, input logic n_rst,
                    input logic [1:0] tx_packet, //the control register for ack/nack/stall
                    input logic [6:0] buffer_occupancy, //buffer occupancy
                    input logic [7:0] tx_packet_data, //the data recieved
                    input logic bit_period_strobe,    //8 bit periods has finished
                    input logic shift_strobe,     //1 bit period has finished for eop
                    output logic eop_en,      //eop enable 
                    output logic cnt_en,      //enable the counter to count 
                    output logic [7:0] data,  //data to be sent to the pts 
                    output logic tx_transfer_error, //transfer error 
                    output logic tx_transfer_active, //transfer active 
                    output logic clear,         // to clear the counter start back from 0 
                    output logic get_tx_packet_data);   //clear the clock
    
    typedef enum bit [3:0] {idle, sync, pid, data0, data1, crc1, crc2, eop1, eop2, eop3} states;
    states state;
    states nextstate;
   
    logic [7:0] nextdata;

    always_ff @ (posedge clk, negedge n_rst) begin 
        if(n_rst == 1'b0) begin
            state <= idle;
            data <= 0;
        end else begin  
            state <= nextstate;
            data <= nextdata;
        end
    end 


    always_comb begin 
        nextstate = state;
        tx_transfer_error = 0;
        nextdata = data;
        cnt_en = 0;
        tx_transfer_active = 0;
        clear = 0;
        eop_en = 0;
        get_tx_packet_data = 0;

        case(state)
            idle: begin 
                tx_transfer_active = 0;
                tx_transfer_error = 0;
                if((tx_packet_data != 4'd0)) begin 
                    nextstate = sync;
                    clear = 1; //clear the counter before going next state
                end else begin 
                    nextstate = idle;
                end
            end
            sync: begin 
                tx_transfer_active = 1;
                cnt_en = 1;
                nextdata = 8'd1; //hard code the sync bit 
                //send nextdata to the pts and should output the values 1 by 1 to the encoder
                if(bit_period_strobe == 1) begin //finish counting 8 bit period 
                    cnt_en = 0;
                    nextstate = pid;
                    clear = 1; //clear before going next state 
                end
            end
            pid: begin 
                cnt_en = 0; //stop counting maybe?
                tx_transfer_active = 1;
                if((tx_packet == 2'd0)) begin 
                    tx_transfer_error = 1;
                    clear = 1;
                    //or just go to error state 
                    nextstate = idle; // if there is an error just go back to idle 
                end
                else if(tx_packet == 2'd2) begin 
                    cnt_en = 1;
                    nextdata = {4'b0010,4'b0100}; //pid for ACK
                    if(bit_period_strobe == 1) begin //8 bit period is done
                        nextstate = eop1;
                        clear = 1;
                    end
                end else if(tx_packet == 4'd3) begin 
                    cnt_en = 1;
                    nextdata = {4'b1010,4'b0101}; //pid for NAK
                    if(bit_period_strobe == 1) begin //8 bit period is done
                        nextstate = eop1;
                        clear = 1;
                    end
                end else if(tx_packet == 2'd1) begin 
                    nextdata = {4'b1011,4'b1101}; //send in the PID for data1
                    cnt_en = 1;
                    if(bit_period_strobe == 1) begin //8 bit period is done
                        nextstate = data1;
                        clear = 1;
                    end
                end else if (tx_packet == 2'd4) begin
                    cnt_en = 1;
                    nextdata = {4'b1110,4'b0111};
                    if(bit_period_strobe == 1) begin //8 bit period is done
                        nextstate = eop1;
                        clear = 1;
                    end
                end else begin 
                    tx_transfer_error = 1;
                    clear = 1;
                    nextstate = idle; //if there is an error just go back to idle
                end
            end 
            data0: begin //get the tx packet data 
                tx_transfer_active = 1;
                get_tx_packet_data = 0;
                cnt_en = 1; //start the timer to shift 
                if(bit_period_strobe == 1) begin 
                    clear = 1;
                    nextstate = data1;
                end 
            end
            data1: begin 
                tx_transfer_active = 1;
                cnt_en = 0;
                get_tx_packet_data = 1;
                if(buffer_occupancy == 0) begin 
                    clear = 1;
                    nextstate = crc1;
                end else begin 
                    clear = 1;
                    nextstate = data0;
                    nextdata = tx_packet_data;
                end
            end 
            crc1: begin
                tx_transfer_active = 1;
                cnt_en = 1;
                nextdata = 8'd1; //set in dummy value for crc bit 
                //need to count for 8 bits here so have to wait for sync done
                if(bit_period_strobe == 1) begin 
                    clear = 1;
                    nextstate = crc2;
                end
            end
            crc2: begin 
                tx_transfer_active = 1;
                cnt_en = 1;
                nextdata = 8'd1; //set in the dumy value for crc bit 
                //need to count for 8 bits here so have to wait for syncdone
                if(bit_period_strobe == 1) begin 
                    clear = 1;
                    nextstate = eop1;
                end 
            end
            eop1: begin
                tx_transfer_active = 1; 
                cnt_en = 1; //start counting
                eop_en = 1;
                //check if a bit period has passed
                if(shift_strobe == 1) begin //finish counting for a bit period 
                    clear = 1;
                    nextstate = eop2;
                end
            end
            eop2: begin  //this will just be used to reset the values back to default
                tx_transfer_active = 1;
                cnt_en = 1; //start counting
                eop_en = 1;//check if a bit period has passed
                if(shift_strobe == 1) begin  //finish counting for a bit period 
                    clear = 1;
                    nextstate = eop3; //maybe need to add in eop3
                end
            end
            eop3: begin 
                tx_transfer_active = 1;
                cnt_en = 1;
                //eop_en = 1;
                if(shift_strobe == 1) begin 
                    clear = 1;
                    nextstate = idle;
                end

            end
            /*
            error: begin 
                tx_transfer_error = 1;
                nextstate = idle;
                
            end 
            */
            default: begin 
                tx_transfer_error = 0;
                nextdata = data;
                cnt_en = 0;
                tx_transfer_active = 0;
                clear = 0;
                eop_en = 0;
                get_tx_packet_data = 0;
            end
        endcase

    end


endmodule