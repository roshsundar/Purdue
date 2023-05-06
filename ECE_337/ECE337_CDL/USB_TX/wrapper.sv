module wrapper (input logic clk, input logic n_rst, input logic store, input logic get, input logic clear,  input logic [7:0] wdata,
                output logic dplus, output logic dminus, output logic tx_transfer_active, input logic [1:0] tx_packet, output logic tx_transfer_error);

    logic [7:0] tx_packet_data;
    logic get_tx_packet_data;
    logic [6:0] buffer_occupancy;
    //rdata is connected to tx_packet_data
    //wdata is connected to tx_data or data 
    
    fifousb fifiomodule (.clk(clk),.n_rst(n_rst),.store(store),.clear(clear), 
                .wdata(wdata),.rdata(tx_packet_data),.buffer_occupancy(buffer_occupancy),.get(get_tx_packet_data));

    usb_tx txmodule (.clk(clk),.n_rst(n_rst),.tx_packet_data(tx_packet_data),
    .buffer_occupancy(buffer_occupancy),.tx_packet(tx_packet),
    .dplus(dplus),.dminus(dminus),.tx_transfer_active(tx_transer_active),
    .tx_transfer_error(tx_transfer_error),.get_tx_packet_data(get_tx_packet_data));
    
endmodule