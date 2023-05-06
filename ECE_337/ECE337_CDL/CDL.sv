module overall_cdl (
    //clock and Reset
    input logic clk, 
    input logic n_rst,
    
    //Master Signals 
    input logic hsel, 
    input logic [3:0] haddr, 
    input logic [1:0] htrans,    
    input logic [1:0] hsize, 
    input logic hwrite, 
    input logic [31:0] hwdata, 
    output logic [31:0] hrdata, 
    output logic hresp, 
    output logic hready,

    //D Mode Logic 
    output logic d_mode, 
            
    //RX Signals 
    input logic dplusin, 
    input logic dminusin, 
            
    //TX Signals 
    output logic dplus, 
    output logic dminus
    );

logic [6:0] buffer_occupancy;
logic clear;
logic store, get;
logic store_rx_data, store_tx_data;
logic get_tx_packet_data, get_rx_packet_data;
logic [7:0] rx_packet_data, tx_packet_data;
logic [7:0] rx_data, tx_data;
logic rx_error, rx_transfer_active, rx_data_ready;
logic tx_error, tx_transer_active;
logic [2:0] rx_packet, tx_packet;
logic [7:0] wdata, rdata;

always_comb begin
    if (store_rx_data) begin
        store = store_rx_data;
        wdata = rx_packet_data;
    end
    else if (store_tx_data) begin
        store = store_tx_data;
        wdata = tx_data;
    end
    else begin
        store = 0;
        wdata = '0;
    end
end

always_comb begin
    if (get_tx_packet_data) begin
        get = get_tx_packet_data;
        rdata = tx_packet_data;
    end
    else if (get_rx_packet_data) begin
        get = get_rx_packet_data;
        rdata = rx_data;
    end
    else begin
        get = 0;
        rdata = '0;
    end
end

//RX Module
usb_rx RX (.clk(clk), .n_rst(n_rst), .d_plus(dplusin), .d_minus(dminusin), .buffer_occ(buffer_occupancy), 
           .flush(clear), .store(store_rx_data), .packet(rx_packet_data), .error(rx_error), 
           .rcving(rx_transfer_active), .data_ready(rx_data_ready), .pid(rx_packet));

usb_tx TX (.clk(clk), .n_rst(n_rst), .tx_packet_data(tx_packet_data),
           .buffer_occupancy(buffer_occupancy), .tx_packet(tx_packet),
           .dplus(dplus), .dminus(dminus), .tx_transfer_active(tx_transer_active),
           .tx_transfer_error(tx_error), .get_tx_packet_data(get_tx_packet_data));

fifousb FIFO (.clk(clk), .n_rst(n_rst), .store(store), .get(get),
              .clear(clear), .wdata(wdata), .rdata(rdata), .buffer_occupancy(buffer_occupancy));

usb_ahb_lite_slave AHB (.clk(clk), .n_rst(n_rst), .rx_packet(rx_packet), .rx_data_ready(rx_data_ready), .rx_transfer_active(rx_transfer_active),
                        .rx_error(rx_error), .buffer_occupancy(buffer_occupancy), .rx_data(rx_data), .get_rx_data(get_rx_packet_data), .store_rx_data(store_rx_data),
                        .tx_data(tx_data), .clear(clear), .tx_packet(tx_packet), .tx_transfer_active(tx_transer_active), .tx_error(tx_error),
                        .hsel(hsel), .haddr(haddr), .hsize(hsize), .htrans(htrans), .hwrite(hwrite), .hwdata(hwdata), .hrdata(hrdata),
                        .hresp(hresp), .hready(hready), .d_mode(d_mode));

endmodule
