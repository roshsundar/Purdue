`timescale 1ns / 10ps

module tb_wrapper();
// Timing related constants
localparam CLK_PERIOD = 10;
localparam BUS_DELAY  = 800ps; // Based on FF propagation delay


// Sizing related constants
localparam DATA_WIDTH      = 2;
localparam ADDR_WIDTH      = 4;
localparam DATA_WIDTH_BITS = DATA_WIDTH * 8;
localparam DATA_MAX_BIT    = DATA_WIDTH_BITS - 1;
localparam ADDR_MAX_BIT    = ADDR_WIDTH - 1;


//*****************************************************************************
// Declare TB Signals (Bus Model Controls)
//*****************************************************************************
// Testing setup signals
logic                      tb_enqueue_transaction;
logic                      tb_transaction_write;
logic                      tb_transaction_fake;
logic [ADDR_MAX_BIT:0]     tb_transaction_addr;
logic [DATA_MAX_BIT:0]     tb_transaction_data;
logic                      tb_transaction_error;
logic [2:0]                tb_transaction_size;
// Testing control signal(s)
logic    tb_enable_transactions;
integer  tb_current_transaction_num;
logic    tb_current_transaction_error;
logic    tb_model_reset;
string   tb_test_case;
integer  tb_test_case_num;
logic [DATA_MAX_BIT:0] tb_test_data;
string                 tb_check_tag;
logic                  tb_mismatch;
logic                  tb_check;


//general system signals
logic tb_clk;
logic tb_n_rst;

//wrapper file signals 
logic [7:0] tb_data;
logic [6:0] tb_tx_buffer_occupancy;
logic [1:0] tb_tx_packet;
logic       tb_dplus;
logic       tb_dminus;
logic       tb_tx_transfer_active;
logic       tb_tx_error;
logic       tb_get_tx_packet_data;
logic       tb_clear;
logic       tb_get;
logic       tb_store;
//expected value
logic       tb_expected_dplus;
logic       tb_expected_dminus;
logic       tb_expected_transfer_active;
logic       tb_expected_tx_error;

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
// Bus Model Instance
//*****************************************************************************
ahb_lite_bus BFM (.clk(tb_clk),
                  // Testing setup signals
                  .enqueue_transaction(tb_enqueue_transaction),
                  .transaction_write(tb_transaction_write),
                  .transaction_fake(tb_transaction_fake),
                  .transaction_addr(tb_transaction_addr),
                  .transaction_data(tb_transaction_data),
                  .transaction_error(tb_transaction_error),
                  .transaction_size(tb_transaction_size),
                  // Testing controls
                  .model_reset(tb_model_reset),
                  .enable_transactions(tb_enable_transactions),
                  .current_transaction_num(tb_current_transaction_num),
                  .current_transaction_error(tb_current_transaction_error),
                  // AHB-Lite-Slave Side
                  .hsel(tb_hsel),
                  .htrans(tb_htrans),
                  .haddr(tb_haddr),
                  .hsize(tb_hsize),
                  .hwrite(tb_hwrite),
                  .hwdata(tb_hwdata),
                  .hrdata(tb_hrdata),
                  .hresp(tb_hresp));

//*****************************************************************************
// DUT Instance
//*****************************************************************************
// usb_tx DUT(.clk(tb_clk),.n_rst(tb_n_rst),
//             .tx_packet_data(tb_tx_packet_data),.tx_packet(tb_tx_packet),.buffer_occupancy(tb_tx_buffer_occupancy),
//             .dplus(tb_dplus),.dminus(tb_dminus),.tx_transfer_active(tb_transfer_active),
//             .tx_transfer_error(tb_tx_error), .get_tx_packet_data(tb_get_tx_packet_data));

wrapper DUT (.clk(tb_clk),.n_rst(tb_n_rst),.dplus(tb_dplus),.dminus(tb_dminus), .store(tb_store),
            .get(tb_get),.clear(tb_clear),.wdata(tb_data),.tx_transfer_active(tb_tx_transfer_active),.tx_packet(tb_tx_packet) ,.tx_transfer_error(tb_tx_error));
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
// Task to cleanly and consistently check DUT output values
task check_outputs;
  input string check_tag;
begin
  tb_mismatch = 1'b0;
  tb_check    = 1'b1;
  if(tb_expected_dplus == tb_dplus) begin // Check passed
    //$info("Correct 'dplus' output %s during %s test case", check_tag, tb_test_case);
  end
  else begin // Check failed
    tb_mismatch = 1'b1;
    $error("Incorrect 'dplus' output %s during %s test case", check_tag, tb_test_case);
  end

  if(tb_expected_dminus == tb_dminus) begin // Check passed
    //$info("Correct 'dminus' output %s during %s test case", check_tag, tb_test_case);
  end
  else begin // Check failed
    tb_mismatch = 1'b1;
    $error("Incorrect 'dminus' output %s during %s test case", check_tag, tb_test_case);
  end

  if(tb_expected_transfer_active == tb_tx_transfer_active) begin // Check passed
    //$info("Correct 'transfer active' output %s during %s test case", check_tag, tb_test_case);
  end
  else begin // Check failed
    tb_mismatch = 1'b1;
    $error("Incorrect 'transfer active' output %s during %s test case", check_tag, tb_test_case);
  end

  if(tb_expected_tx_error == tb_tx_error) begin // Check passed
    //$info("Correct 'tx_error' output %s during %s test case", check_tag, tb_test_case);
  end
  else begin // Check failed
    tb_mismatch = 1'b1;
    $error("Incorrect 'tx_error' output %s during %s test case", check_tag, tb_test_case);
  end

  // Wait some small amount of time so check pulse timing is visible on waves
  #(0.1);
  tb_check =1'b0;
end
endtask


//*****************************************************************************
// Bus Model Usage Related TB Tasks
//*****************************************************************************
// Task to pulse the reset for the bus model
task reset_model;
begin
  tb_model_reset = 1'b1;
  #(0.1);
  tb_model_reset = 1'b0;
end
endtask

task init_expected_outs;
begin 
  tb_expected_dplus = 1;
  tb_expected_dminus = 0;
  tb_expected_transfer_active = 0; 
  tb_expected_tx_error = 0;
end
endtask
//Main test bench process
initial begin
    tb_test_case = "Initialization";
    tb_test_case_num = -1;
    tb_n_rst =1'b1;
    //initialize the variables 

    #(0.1);

    reset_model();

  //*****************************************************************************
  // Power-on-Reset Test Case
  //*****************************************************************************
  // Update Navigation Info
  tb_test_case     = "Power on Reset";
  tb_test_case_num = tb_test_case_num + 1;
  
  //setup the controller with active values for reset check
  tb_tx_packet = 0;
  tb_data = 0;
  tb_store = 0;
  tb_get = 0;
  tb_clear = 0;

  // Reset the DUT
  reset_dut();

  // Check outputs for reset state
  init_expected_outs();
  check_outputs("after DUT reset");

  // Give some visual spacing between check and next test case start
  #(CLK_PERIOD * 20);

  //*****************************************************************************
  // Test Case: General test case - works just fine
  //*****************************************************************************
  tb_test_case = "Data functionality test"; //tested with multiple data inputs 
  tb_test_case_num = tb_test_case_num + 1; 

  //setup the desired inputs 
  
  tb_store = 1; //store the data 
  tb_data = 8'd10; //data 
  #(CLK_PERIOD); //wait for a clock cycle
  tb_store = 0;
  #(CLK_PERIOD);
  tb_store = 1; //store the data 
  tb_data = 8'd11; //data
  #(CLK_PERIOD); 
  tb_store = 0; //turn off store 

  tb_tx_packet = 2'd1; //control register to send pid for data1
  
  //need to figure out the buffer_occupancy

  tb_expected_transfer_active = 1;
  tb_expected_tx_error = 0;
  // tb_expected_dminus;
  // tb_expected_dplus;
  check_outputs("Data functionality test");
  #(CLK_PERIOD * 500);


  
  //*****************************************************************************
  // Test Case: ACK TEST CASE - works just fine
  //*****************************************************************************
   reset_dut();
  tb_test_case = "ACK test";
  tb_test_case_num = tb_test_case_num + 1;
  
  //not storing anything or sending data
  tb_store = 1;
  tb_data = 8'd1; //so can go next state
  #(CLK_PERIOD);
  tb_store = 0;
  tb_tx_packet = 2'd2; //go to pid for ack 

  //need to find out if there is a way to stop at idle here 

  tb_expected_transfer_active = 1;
  tb_expected_tx_error = 0;
  check_outputs("ACK functionality test");
  #(CLK_PERIOD * 170);

  //*****************************************************************************
  // Test Case: NACK TEST CASE - works just fine 
  //*****************************************************************************
  tb_test_case = "NACK test";
  tb_test_case_num = tb_test_case_num + 1;
  
  reset_dut();
  //not storing anything or sending data
  tb_store = 1;
  tb_data = 8'd1; //so can go next state
  #(CLK_PERIOD);
  tb_store = 0;
  tb_tx_packet = 2'd3; //go to pid for ack 
  
  //need to find out if there is a way to stop at idle here 

  tb_expected_transfer_active = 1;
  tb_expected_tx_error = 0;
  check_outputs("NACK functionality test");
  #(CLK_PERIOD * 170); 
  //just need to find out how to stop transitioning from idle to sync seems to keep repeating it 

  //*****************************************************************************
  // Test Case: ERROR TEST CASE - transfer error works but not sure if it supposed to be like that 
  //*****************************************************************************
  tb_test_case = "ERROR test";
  tb_test_case_num = tb_test_case_num + 1;

  reset_dut();
  tb_store = 1;
  tb_data = 8'd43;
  #(CLK_PERIOD);
  tb_store = 0;
  tb_tx_packet = 2'd0;
  #(CLK_PERIOD);
  tb_tx_buffer_occupancy = 0;


  tb_tx_packet = 2'd0;
  tb_expected_tx_error = 0;
  tb_expected_transfer_active =1;

  check_outputs("ERROR functionality test");
  #(CLK_PERIOD * 400);
  $stop;
end
endmodule