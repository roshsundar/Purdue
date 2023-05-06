/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP1
// Date      : Thu Feb  2 17:28:18 2023
/////////////////////////////////////////////////////////////


module sync_low ( clk, n_rst, async_in, sync_out );
  input clk, n_rst, async_in;
  output sync_out;
  wire   Q1_D2;

  DFFSR Q1_D2_reg ( .D(async_in), .CLK(clk), .R(n_rst), .S(1'b1), .Q(Q1_D2) );
  DFFSR sync_out_reg ( .D(Q1_D2), .CLK(clk), .R(n_rst), .S(1'b1), .Q(sync_out)
         );
endmodule

