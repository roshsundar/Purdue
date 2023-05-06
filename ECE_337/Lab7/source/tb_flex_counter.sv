// $Id: $
// File name:   tb_flex_counter.sv
// Created:     2/3/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: test bench for flex counter with default (4-bit) count

`timescale 1ns / 10ps

module tb_flex_counter
();
    // Define local parameters used by the test bench
    localparam  NUM_CNT_BITS = 4;
    localparam  CLK_PERIOD    = 2.5;
    //localparam  CLK_PERIOD    = 1;
    localparam  FF_SETUP_TIME = 0.190;
    localparam  FF_HOLD_TIME  = 0.100;
    localparam  CHECK_DELAY   = (CLK_PERIOD - FF_SETUP_TIME); // Check right before the setup time starts

    // Declare test bench signals
    string tb_test_case;

    // Declare DUT portmap signals
    reg tb_clk;
    reg tb_n_rst;
    reg tb_clear;
    reg tb_count_enable;
    reg [NUM_CNT_BITS-1:0] tb_rollover_val;
    reg [NUM_CNT_BITS-1:0] tb_count_out;
    reg tb_rollover_flag;

    // DUT Port map
    flex_counter DUT
    ( 
        .clk( tb_clk ),
        .n_rst( tb_n_rst ),
        .clear( tb_clear ),
        .count_enable( tb_count_enable ),
        .rollover_val( tb_rollover_val ),
        .count_out( tb_count_out ),
        .rollover_flag( tb_rollover_flag ) 
    );

    // Task to cleanly and consistently check DUT output values
    task check_output;
        input logic [NUM_CNT_BITS-1:0] expected_count;
        input logic expected_flag;
    begin
        if(expected_count == tb_count_out) begin // Check passed
        $info("CORRECT: count_out for Test Case %s ", tb_test_case);
        end
        else begin // Check failed
        $error("INCORRECT: count_out is %d, expected %d for Test Case %s ", tb_count_out, expected_count, tb_test_case);
        end

        if(expected_flag == tb_rollover_flag) begin // Check passed
        $info("CORRECT: rollover_flag for Test Case %s ", tb_test_case);
        end
        else begin // Check failed
        $error("INCORRECT: rollover_flag is %d, expected %d for Test Case %s ", tb_rollover_flag, expected_flag, tb_test_case);
        end
    end
    endtask

    // Task to cleanly and consistently check DUT output values
    task clear_DUT;
    begin
        @(posedge tb_clk);
		tb_clear = 1'b1;
		@(posedge tb_clk);
		tb_clear = 1'b0;
    end
    endtask

    // Clock generation block
    always
    begin
        // Start with clock low to avoid false rising edge events at t=0
        tb_clk = 1'b0;
        // Wait half of the clock period before toggling clock value (maintain 50% duty cycle)
        #(CLK_PERIOD/2.0);
        tb_clk = 1'b1;
        // Wait half of the clock period before toggling clock value via rerunning the block (maintain 50% duty cycle)
        #(CLK_PERIOD/2.0);
    end

    initial
    begin

        // ============================================================================= Test case 1: Power-on-Reset
        clear_DUT();
        tb_test_case = "[Power-on-Reset]";

        tb_n_rst = 0;
        tb_clear = 1'b0;
        tb_rollover_val = 2;
        tb_count_enable = 0;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(0, 0);

        // ============================================================================= Test case 2: Rollover for rollover value not a power of two
        clear_DUT();
        tb_test_case = "[Rollover for rollover value not a power of two]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 3;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(3, 1);

        // ============================================================================= Test case 3: Continuous Counting
        clear_DUT();
        tb_test_case = "[Continuous Counting]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 4;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(4, 1);

        @(posedge tb_clk);
        #(CHECK_DELAY);
        check_output(1, 0);

        // ============================================================================= Test case 4: Discontinuous Counting
        clear_DUT();
        tb_test_case = "[Discontinuous Counting]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 2;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        tb_count_enable = 1'b0;
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        tb_count_enable = 1'b1;
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(2, 1);
        
        // ============================================================================= Test case 5: Clear While Counting
        clear_DUT();
        tb_test_case = "[Clear While Counting]";

        tb_n_rst = 1;
        tb_clear = 1'b1;
        tb_rollover_val = 4;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(0, 0);

        // ============================================================================= Test case 6: Count Short of Rollover
        clear_DUT();
        tb_test_case = "[Count Short of Rollover]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 7;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(6, 0);

        // ============================================================================= Test case 7: Count to Max Value (15)
        clear_DUT();
        tb_test_case = "[Count to Max Value (15)]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 15;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(15, 1);

        // ============================================================================= Test case 8: Count to rollover and hold flag
        clear_DUT();
        tb_test_case = "[Count to Max Value (15)]";

        tb_n_rst = 1;
        tb_clear = 1'b0;
        tb_rollover_val = 5;
        tb_count_enable = 1'b1;

        // Wait for DUT to process the stimulus
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        tb_count_enable = 1'b0;

        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);
        @(posedge tb_clk);

        // Move away from rising edge and allow for propagation delays before checking
        #(CHECK_DELAY);
        check_output(5, 1);
    $stop;
    end
endmodule