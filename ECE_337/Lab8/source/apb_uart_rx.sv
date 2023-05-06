// $Id: $
// File name:   apb_uart_rx.sv
// Created:     3/3/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: full design module that connects the dedicated APB-Slave interface and UART Reciever modules together
// to form the overall SoC peripheral.

module apb_uart_rx
(
    input logic clk, n_rst, serial_in, psel,
    input logic [2:0] paddr,
    input logic penable, pwrite,
    input logic [7:0] pwdata,
    output logic [7:0] prdata,
    output logic pslverr
);
    logic [7:0] rx_data;
    logic data_ready;
    logic overrun_error;
    logic framing_error;
    logic data_read;
    logic [3:0] data_size;
    logic [13:0] bit_period;

    apb_slave SLAVE (.clk(clk), .n_rst(n_rst), .rx_data(rx_data), .data_ready(data_ready), .overrun_error(overrun_error), .framing_error(framing_error), .data_read(data_read), .psel(psel), 
    .paddr(paddr), .penable(penable), .pwrite(pwrite), .pwdata(pwdata), .prdata(prdata), .pslverr(pslverr), .data_size(data_size), .bit_period(bit_period)
    );

    rcv_block UART (.clk(clk), .n_rst(n_rst), .serial_in(serial_in), .data_read(data_read), .data_size(data_size), .bit_period(bit_period),
    .rx_data(rx_data), .data_ready(data_ready), .overrun_error(overrun_error), .framing_error(framing_error));
endmodule