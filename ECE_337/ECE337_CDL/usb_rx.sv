// $Id: $
// File name:   usb_rx.sv
// Created:     4/24/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Full USB RX module

module usb_rx (
    input logic clk, n_rst,
    input logic d_plus, d_minus,
    input logic [6:0] buffer_occ,
    output logic flush, store,
    output logic [7:0] packet,
    output logic error, rcving, data_ready,
    output logic [2:0] pid
);
    logic d_plus_sync, d_minus_sync, d_edge, shift_en, eop, d_orig, byte_rcvd;
    logic [7:0] rcv_byte;

    sync_high SYNC_H (.clk(clk), .n_rst(n_rst), .async_in(d_plus), .sync_out(d_plus_sync));
    sync_low  SYNC_L (.clk(clk), .n_rst(n_rst), .async_in(d_minus), .sync_out(d_minus_sync));

    edge_detect EDGE (.clk(clk), .n_rst(n_rst), .d_plus_sync(d_plus_sync), .d_edge(d_edge));

    decode DECODE (.clk(clk), .n_rst(n_rst), .d_plus_sync(d_plus_sync), .shift_en(shift_en), .eop(eop), .d_orig(d_orig));

    eop_detect EOP (.d_plus_sync(d_plus_sync), .d_minus_sync(d_minus_sync), .eop(eop));

    timer TIMER (.clk(clk), .n_rst(n_rst), .enable_timer(rcving), .shift_strobe(shift_en), .byte_rcvd(byte_rcvd));

    sr_8bit SR (.clk(clk), .n_rst(n_rst), .shift_strobe(shift_en), .serial_in(d_orig), .rcv_byte(rcv_byte));

    rcu RCU (.clk(clk), .n_rst(n_rst), .d_edge(d_edge), .byte_rcvd(byte_rcvd), .eop(eop), .shift_en(shift_en), .buffer_occ(buffer_occ), .rcv_byte(rcv_byte), 
    .flush(flush), .store(store), .rcving(rcving), .data_ready(data_ready), .error(error), .pid(pid), .prev_byte(packet));
endmodule