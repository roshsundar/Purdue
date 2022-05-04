module printer (
  input clk, rst, activate, txready,
  input [2:0] num,
  input [7:0] char_in,
  output logic done_printing, txclk,
  output logic [7:0] txdata
);

  // Sets of messages from which the printer will select one, and send out
  logic [511:0] msg [7:0];
  assign msg[0] = {272'b0, "Ready to play? Press any key: "};
  assign msg[1] = {440'b0, "\r\nGuess: "};
  assign msg[2] = {152'b0, "You win!  Press 3-0-W on the FPGA to reset.\r\n"};
  // when user is entering characters, print them so user can see what they're typing
  // this is also called echoback
  assign msg[3] = {504'b0, char_in};
  // COLOR_Y - to color the next letter yellow
  assign msg[4] = {472'b0, 8'h1b, 8'h5b, 8'h33, 8'h33, 8'h6d};
  // COLOR_G - to color the next letter green
  assign msg[5] = {472'b0, 8'h1b, 8'h5b, 8'h33, 8'h32, 8'h6d};
  // COLOR_W - to color the next letter white
  assign msg[6] = {472'b0, 8'h1b, 8'h5b, 8'h33, 8'h37, 8'h6d};
  // unused, so we'll initialize to zero
  assign msg[7] = 512'b0;

  // this section sets the number of characters for each message
  // so that the printer knows where to stop
  logic [15:0] len, senlen;
  always_comb begin
    case(num)
      0: senlen = 30*8;
      1: senlen = 9*8;
      2: senlen = 46*8;
      3: senlen = 1*8;  
      4,5,6: senlen = 5*8;
      default: senlen = 0;
    endcase
  end

  // are we printing anything at all? 
  logic printing;
  // if true, set data before clock, otherwise assert clock
  logic set_data;

  // use the indentation to determine whether a statement falls beneath an if/else statement!
  always_ff @(posedge clk, posedge rst)
    if (rst == 1) begin
      txclk <= 0; txdata <= 0; done_printing <= 0; printing <= 0; set_data <= 0;
    end
    else begin
      if (activate == 0 && printing == 0 && done_printing == 1)
        done_printing <= 0;
      else if (activate == 1 && printing == 0) begin
        set_data <= 0;       // reinitializing for a new message to be printed
        printing <= 1;       // bookkeeping to know that a message is being printed
        done_printing <= 0;  // if we're just starting to print, we can't be done printing!  
        len <= senlen;       // initialize length to length of message, and count down by 8 bits (1 letter)
        end
      else if (printing == 1 && len == 0) begin
        printing <= 0;       // we're done printing, don't print any more!
        txclk <= 0;          // reset for when we need to print the next message
        set_data <= 0;       // reset for when we need to print the next message
        done_printing <= 1;  // we're done printing, so indicate that to the controller
      end
      else if (txready == 1 && printing == 1) begin
        if (~set_data) begin       // set our data BEFORE clock, so that we do not have setup time violations
          if (num == 3 && char_in == 127)            // if the character being received is a backspace
            txdata <= 8'd8;                      // send the code for a backspace to make your cursor move left!
          else
            txdata <= msg[num][(len - 1) -: 8];
            // (len - 1) -: 8, in Verilog, can be expanded to (len-1) : (len-1-(8-1))
            // so if you're trying to send the last character, len would be 8, which 
            // would cause the expression to evaluate to [7:0]
          txclk <= 0;
          set_data <= 1;
        end
        else begin
          txclk <= 1;
          set_data <= 0;
          len <= len - 8;
        end
      end
    end

endmodule