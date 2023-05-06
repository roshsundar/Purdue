// $Id: $
// File name:   tb_usb_rx.sv
// Created:     4/24/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Testbench for USB RX

`timescale 1ns / 10ps

module tb_usb_rx();
// Timing related constants
localparam CLK_PERIOD = 10;

//*****************************************************************************
// General System signals
//*****************************************************************************
logic tb_clk;
logic tb_n_rst;

//*****************************************************************************
// Clock Generation Block
//*****************************************************************************
// Clock generation block
always begin
  // Start with clock low to avoid false rising edge events at t=0
  tb_clk = 1'b0;
  // Wait half of the clock period before toggling clock value (maintain 50% duty cycle)
  #(CLK_PERIOD/2.0);
  tb_clk = 1'b1;
  // Wait half of the clock period before toggling clock value via rerunning the block (maintain 50% duty cycle)
  #(CLK_PERIOD/2.0);
end

//*****************************************************************************
// Testing Signals
//*****************************************************************************
integer tb_i;
integer tb_i_val;
string tb_test_case;
integer tb_test_case_num;

//*****************************************************************************
// DUT Signals
//*****************************************************************************
// inputs
logic           tb_d_plus, tb_d_minus;
logic [6:0]     tb_buffer_occ;
// outputs
logic           tb_flush, tb_store;
logic [7:0]     tb_packet;
logic           tb_error, tb_rcving, tb_data_ready;
logic [2:0]     tb_pid;

//*****************************************************************************
// DUT Instance
//*****************************************************************************
usb_rx DUT (
    .clk(tb_clk), .n_rst(tb_n_rst), 
    .d_plus(tb_d_plus), .d_minus(tb_d_minus), .buffer_occ(tb_buffer_occ), 
    .flush(tb_flush), .store(tb_store), .packet(tb_packet), .error(tb_error), .rcving(tb_rcving), .data_ready(tb_data_ready), .pid(tb_pid)
); 

//*****************************************************************************
// DUT Related TB Tasks
//*****************************************************************************
// Task for standard DUT reset procedure
task reset_dut;
begin
    // Activate the reset
    tb_n_rst = 1'b0;

    // Maintain the reset for more than one cycle
    @(posedge tb_clk);
    @(posedge tb_clk);

    // Wait until safely away from rising edge of the clock before releasing
    @(negedge tb_clk);
    tb_n_rst = 1'b1;

    // Leave out of reset for a couple cycles before allowing other stimulus
    // Wait for negative clock edges, 
    // since inputs to DUT should normally be applied away from rising clock edges
    @(negedge tb_clk);
    @(negedge tb_clk);
end
endtask

// translates byte into d+, d- signals
task byte_signal;
    input [7:0] in_byte;
begin
    for (tb_i = 0; tb_i < 8; tb_i++)
    begin
        tb_i_val = in_byte[tb_i];
        if (tb_i_val == 1'b0) begin
            tb_d_plus = !tb_d_plus;
            tb_d_minus = !tb_d_minus; 
        end
        // else: d+,d- are the same

        #(CLK_PERIOD * 100.0 / 12.0);
    end
    $info("Byte Sent");
end
endtask

// translates byte into d+, d- signals
// with an error
task byte_signal_err;
    input [7:0] in_byte;
begin
    for (tb_i = 0; tb_i < 8; tb_i++)
    begin
        tb_i_val = in_byte[tb_i];
        if (tb_i == 4) begin
            tb_d_plus = 0;
            tb_d_minus = 0;
        end
        else if (tb_i_val == 1'b0) begin
            tb_d_plus = !tb_d_plus;
            tb_d_minus = !tb_d_minus; 
        end
        // else: d+,d- are the same

        #(CLK_PERIOD * 100.0 / 12.0);
    end
    $info("Byte Sent");
end
endtask

//*****************************************************************************
//*****************************************************************************
// Main TB Process
//*****************************************************************************
//*****************************************************************************
initial begin
    // Initialize Test Case Navigation Signals
    tb_test_case       = "Initilization";
    tb_test_case_num   = -1;
    tb_d_plus = 1'b1;
    tb_d_minus = 1'b0;
    reset_dut();


    // Test Case 1: Correct SYNC byte [passed] [waves_sync.do]
    //*****************************************************************************
    /*
    tb_test_case       = "SYNC Correct";
    tb_test_case_num   = tb_test_case_num + 1;
    byte_signal(8'b10000000); // sync
    #(CLK_PERIOD * 4)
    */

    // Test Case 2: Wrong SYNC byte [passed] [waves_sync.do]
    //*****************************************************************************
    /*
    tb_test_case       = "SYNC Wrong";
    tb_test_case_num   = tb_test_case_num + 1;
    byte_signal(8'b10101000); // wrong sync
    #(CLK_PERIOD * 4)

    tb_d_plus = 1'b0;
    tb_d_minus = 1'b0;
    #(CLK_PERIOD * 4)
    */

    // Test Case 3: Wrong PID byte [passed] [waves_sync.do]
    //*****************************************************************************
    /*
    tb_test_case       = "PID Wrong";
    tb_test_case_num   = tb_test_case_num + 1;
    byte_signal(8'b10000000); // sync
    byte_signal(8'b11111111); // wrong pid
    #(CLK_PERIOD * 4)

    tb_d_plus = 1'b0;
    tb_d_minus = 1'b0;
    #(CLK_PERIOD * 4)
    */

    // Test Case 4: ACK/NACK Received [passed] [waves_pid.do]
    //*****************************************************************************
    /*
    tb_test_case       = "ACK/NACK";
    tb_test_case_num   = tb_test_case_num + 1;
    byte_signal(8'b10000000); // sync
    byte_signal(8'b01011010); // ACK = 11010010 NACK = 01011010
    #(CLK_PERIOD * 4)
    */

    // Test Case 4: IN/OUT Received [passed] [waves_pid.do]
    //*****************************************************************************
    /*
    tb_test_case       = "IN/OUT";
    tb_test_case_num   = tb_test_case_num + 1;
    byte_signal(8'b10000000); // sync
    byte_signal(8'b01101001); // IN = 01101001 OUT = 11100001
    byte_signal(8'b00000000); // byte 1
    byte_signal(8'b11111111); // byte 2
    #(CLK_PERIOD * 4)
    */

    // Test Case 4: DATA 3 bytes recieved
    //*****************************************************************************
    /*
    tb_test_case       = "DATA 3 Bytes";
    tb_test_case_num   = tb_test_case_num + 1;
    tb_buffer_occ = 7'd0;
    byte_signal(8'b10000000); // sync
    tb_buffer_occ += 7'd1;
    byte_signal(8'b11000011); // DATA
    tb_buffer_occ += 7'd1;

    byte_signal(8'b10000001); // byte 1
    tb_buffer_occ += 7'd1;
    byte_signal(8'b01111111); // byte 2
    tb_buffer_occ += 7'd1;
    byte_signal(8'b01010101); // byte 3
    tb_buffer_occ += 7'd1;
    byte_signal(8'b11111111); // crc 1
    byte_signal(8'b11111111); // crc 2

    // EOP
    tb_d_plus = 1'b0;
    tb_d_minus = 1'b0;
    #(CLK_PERIOD * 8)
    */

    // Test Case 5: DATA Early EOP
    //*****************************************************************************
    tb_test_case       = "DATA EOP ERR";
    tb_test_case_num   = tb_test_case_num + 1;
    tb_buffer_occ = 7'd0;
    byte_signal(8'b10000000); // sync
    tb_buffer_occ += 7'd1;
    byte_signal(8'b11000011); // DATA
    tb_buffer_occ += 7'd1;

    byte_signal(8'b10000001); // byte 1
    tb_buffer_occ += 7'd1;

    byte_signal_err(8'b00000000);

    $stop();
end
endmodule