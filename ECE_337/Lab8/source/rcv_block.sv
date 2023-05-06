// $Id: $
// File name:   rcv_block.sv
// Created:     2/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: UART Reciever.

module rcv_block
(
    input logic clk, n_rst, serial_in, data_read,
    input logic [3:0] data_size,
    input logic [13:0] bit_period,
    output logic [7:0] rx_data,
    output logic data_ready, overrun_error, framing_error
);

    logic new_packet_detected;
    logic shift_strobe;
    logic stop_bit;
    logic [7:0] packet_data;
    logic enable_timer;
    logic packet_done;
    logic sbc_clear;
    logic sbc_enable;
    logic load_buffer;

    start_bit_det Detector (.clk(clk), .n_rst(n_rst), .serial_in(serial_in), .start_bit_detected(), .new_packet_detected(new_packet_detected));
    
    sr_9bit ShiftReg (.clk(clk), .n_rst(n_rst), .shift_strobe(shift_strobe), .data_size(data_size), .serial_in(serial_in), .packet_data(packet_data), .stop_bit(stop_bit));

    timer TimingControl (.clk(clk), .n_rst(n_rst), .enable_timer(enable_timer), .shift_strobe(shift_strobe), .packet_done(packet_done), .data_size(data_size), .bit_period(bit_period));

    rcu RCU (.clk(clk), .n_rst(n_rst), .new_packet_detected(new_packet_detected), .packet_done(packet_done), .framing_error(framing_error),
            .sbc_clear(sbc_clear), .sbc_enable(sbc_enable), .load_buffer(load_buffer), .enable_timer(enable_timer)
    );

    stop_bit_chk StopChk (.clk(clk), .n_rst(n_rst), .sbc_clear(sbc_clear), .sbc_enable(sbc_enable), .stop_bit(stop_bit), .framing_error(framing_error));

    rx_data_buff RXbuff (.clk(clk), .n_rst(n_rst), .load_buffer(load_buffer), .packet_data(packet_data), .data_read(data_read), 
                        .rx_data(rx_data), .data_ready(data_ready), .overrun_error(overrun_error)
    );    
endmodule