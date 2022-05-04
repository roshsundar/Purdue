`default_nettype none
// Empty top module

module top (
  // I/O ports
  input  hz100, reset,
  input  [20:0] pb,
  output [7:0] left, right,
         ss7, ss6, ss5, ss4, ss3, ss2, ss1, ss0,
  output red, green, blue,

  // UART ports
  output [7:0] txdata,
  input  [7:0] rxdata,
  output txclk, rxclk,
  input  txready, rxready
);

  logic flash, hz1;
  logic [7:0] ctr;
  
  //assign blue = flash;
  
  always_ff @(posedge hz100, posedge reset)
  begin
    if (reset == 1) begin
      hz1 <= 0;
    end
    else begin
      hz1 <= ctr == 8'd49;
    end
  end
  
  always_ff @(posedge hz1, posedge reset)
  begin
    if (reset == 1) begin
      flash <= 0;
    end
    else begin
      flash <= ~flash;
    end
  end
  
  hangman hg (.hz100(hz100), .reset(pb[19]), .hex(pb[15:10]), .ctrdisp(ss7[6:0]), .letterdisp({ss3[6:0], ss2[6:0], ss1[6:0], ss0[6:0]}), .win(green), .lose(red), .flash(flash));
  count8du c8_1 (.clk(hz100), .rst(reset), .enable(1'b1), .DIR(1'b0), .MAX(8'd49), .out(ctr));
  
endmodule

module count8du (
  input clk, rst, enable, DIR,
  input [7:0] MAX,
  output[7:0] out
);

  logic [7:0] Q, next_Q;
  assign out = Q;

  always_ff @(posedge clk, po//assign blue = flash;sedge rst)
  begin
    if (rst == 1) begin
      Q <= 8'd0;
    end
    else if (enable == 1)
    begin
      Q <= next_Q;
    end
  end
  
  always_comb
  begin
    if (DIR == 0) begin
      if (Q == 0) begin
        next_Q = MAX;
      end
      else begin
        next_Q = Q - 1;
      end
    end
    else begin
      if (Q == MAX) begin
        next_Q = 0;
      end
      else begin
        next_Q = Q + 1;
      end
    end
  end

endmodule

module ssdec (
  input logic [3:0] in,
  input logic enable,
  output logic [6:0] out
);

    logic [6:0] SEG7 [15:0];
    
    assign SEG7[4'h0] = 7'b0111111;
    assign SEG7[4'h1] = 7'b0000110;
    assign SEG7[4'h2] = 7'b1011011;
    assign SEG7[4'h3] = 7'b1001111;
    assign SEG7[4'h4] = 7'b1100110;
    assign SEG7[4'h5] = 7'b1101101;
    assign SEG7[4'h6] = 7'b1111101;
    assign SEG7[4'h7] = 7'b0000111;
    assign SEG7[4'h8] = 7'b1111111;
    assign SEG7[4'h9] = 7'b1100111;
    assign SEG7[4'ha] = 7'b1110111;
    assign SEG7[4'hb] = 7'b1111100;
    assign SEG7[4'hc] = 7'b0111001;
    assign SEG7[4'hd] = 7'b1011110;
    assign SEG7[4'he] = 7'b1111001;
    assign SEG7[4'hf] = 7'b1110001;
    assign out[6:0] = enable == 1 ? SEG7[in] : 0;
  
  
endmodule