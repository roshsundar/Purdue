// $Id: $
// File name:   tb_moore.sv
// Created:     2/15/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: testbench for mealy.sv

`timescale 1ns / 10ps

module tb_mealy();
    // Define parameters
    // Common parameters
    localparam CLK_PERIOD        = 2.5;
    localparam PROPAGATION_DELAY = 0.8; // Allow for 800 ps for FF propagation delay

    localparam MAX_STREAM_SIZE = 20;

    // Declare Test Case Signals
    integer tb_test_num;
    string  tb_test_case;
    
    integer tb_bit_num;

    // Declare the Test Bench Signals for Expected Results
    logic tb_test_data [];

    // Declare DUT Connection Signals
    logic tb_clk;
    logic tb_n_rst;
    logic tb_i;
    logic tb_o;

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

    // Task to manage the timing of sending one bit to FSM
    task send_bit;
        input logic bit_to_send;
    begin
        // Synchronize to the negative edge of clock to prevent timing errors
        @(negedge tb_clk);
        
        // Set the value of the bit
        tb_i = bit_to_send;

        // Wait for the value to have been shifted in on the rising clock edge
        @(posedge tb_clk);
        #(PROPAGATION_DELAY);
    end
    endtask

    // Task to contiguosly send a stream of bits to FSM
    task send_stream;
        input logic bit_stream [];
    begin
        // Coniguously stream out all of the bits in the provided input vector
        for(tb_bit_num = 0; tb_bit_num < bit_stream.size(); tb_bit_num++) begin
            // Send the current bit
            send_bit(bit_stream[tb_bit_num]);
        end
    end
    endtask

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

    // DUT Portmap
    mealy DUT (.clk(tb_clk), .n_rst(tb_n_rst), .i(tb_i), .o(tb_o));

    // Test bench main process
    initial begin
        // Initialize all of the test inputs
        tb_n_rst = 1;
        tb_i = 0;
        tb_test_num         = 0;    // Initialize test case counter
        tb_test_case        = "Test bench initializaton";

        reset_dut();

        // ************************************************************************
        // Test Case 1: full coverage
        // ************************************************************************
        reset_dut();
        tb_test_num         = 1;    // Initialize test case counter
        tb_test_case        = "full coverage";

        tb_test_data = {1'b0, 1'b0, 1'b1, 1'b1, 1'b0, 1'b1, 1'b1, 1'b1, 1'b0, 1'b1, 1'b0};

        send_stream(tb_test_data);

        #(10);
        
        
    $stop;
    end
endmodule