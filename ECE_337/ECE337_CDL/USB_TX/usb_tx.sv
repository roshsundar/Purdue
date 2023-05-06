module usb_tx(input logic clk, input logic n_rst,
              input logic [7:0] tx_packet_data, input logic [6:0] buffer_occupancy,
              input logic [1:0] tx_packet, output logic dplus, output logic dminus,
              output logic tx_transfer_active, output logic tx_transfer_error,  output logic get_tx_packet_data);


    logic bit_strobe;   //finished with 1 bit period
    logic bit_finished; //finished with 8 bit periods
    logic clear;
    logic cnt_en;
    logic serial_out;
    logic [7:0] data;
    logic load_enable;



    //controller
    tx_controller controller(.clk(clk),.n_rst(n_rst),.tx_packet(tx_packet),.buffer_occupancy(buffer_occupancy),
                            .tx_packet_data(tx_packet_data),.bit_period_strobe(bit_finished),
                            .shift_strobe(bit_strobe),.eop_en(eop_en),
                            .cnt_en(cnt_en), .data(data),
                            .tx_transfer_error(tx_transfer_error),.tx_transfer_active(tx_transfer_active),
                            .clear(clear), .get_tx_packet_data(get_tx_packet_data));
    
    //timer
    //bit_strobe counts for 1 bit period - trigger in bit_strobe within the controller
    //bit_finished counts for 8 bit period - trigger bit_period_strobe
    counter timer (.clk(clk),.n_rst(n_rst),.cnt_up(cnt_en), 
                    .clear(clear), .bit_strobe(bit_strobe),
                    .bit_finished(bit_finished),.eop_finished(bit_strobe),
                    .load_enable(load_enable));
    
    //register
    //shift enable should be rollover flag once it counts to 8 emmited from rollover flag 
    //load enable should start loading at counting to 4  and bit period count is 0 
    //parallel_in comes from controller
    //serial out connected to encoder
    flex_pts_sr #(.NUM_BITS(8),.SHIFT_MSB(1)) register(.clk(clk),.n_rst(n_rst),
                        .shift_enable(bit_strobe),.load_enable(load_enable),
                        .parallel_in(data),.serial_out(serial_out));
    


    //encoder
    //eop_trigger from state machine that enables the eop 
    //serial_data is from register
    tx_encoder encoder(.clk(clk),.n_rst(n_rst), 
                        .serial_data(serial_out),
                        .dplus(dplus),.dminus(dminus),
                        .eop_trigger(eop_en), .shift_strobe(bit_strobe));



endmodule