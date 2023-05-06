/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : K-2015.06-SP1
// Date      : Tue Feb  7 17:52:45 2023
/////////////////////////////////////////////////////////////


module flex_counter ( clk, n_rst, clear, count_enable, rollover_val, count_out, 
        rollover_flag );
  input [3:0] rollover_val;
  output [3:0] count_out;
  input clk, n_rst, clear, count_enable;
  output rollover_flag;
  wire   n48, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58, n59, n60, n61,
         n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72, n73, n74, n75,
         n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86, n87, n88, n89;

  DFFSR \count_out_reg[0]  ( .D(n52), .CLK(clk), .R(n_rst), .S(1'b1), .Q(
        count_out[0]) );
  DFFSR \count_out_reg[3]  ( .D(n49), .CLK(clk), .R(n_rst), .S(1'b1), .Q(
        count_out[3]) );
  DFFSR \count_out_reg[1]  ( .D(n51), .CLK(clk), .R(n_rst), .S(1'b1), .Q(
        count_out[1]) );
  DFFSR \count_out_reg[2]  ( .D(n50), .CLK(clk), .R(n_rst), .S(1'b1), .Q(
        count_out[2]) );
  DFFSR rollover_flag_reg ( .D(n48), .CLK(clk), .R(n_rst), .S(1'b1), .Q(
        rollover_flag) );
  MUX2X1 U47 ( .B(n53), .A(n54), .S(n55), .Y(n52) );
  OAI21X1 U48 ( .A(n56), .B(n54), .C(n57), .Y(n53) );
  INVX1 U49 ( .A(n58), .Y(n56) );
  MUX2X1 U50 ( .B(n59), .A(n60), .S(count_out[1]), .Y(n51) );
  NAND2X1 U51 ( .A(n61), .B(count_out[0]), .Y(n59) );
  INVX1 U52 ( .A(n62), .Y(n50) );
  MUX2X1 U53 ( .B(n63), .A(n64), .S(count_out[2]), .Y(n62) );
  MUX2X1 U54 ( .B(n65), .A(n66), .S(count_out[3]), .Y(n49) );
  AOI21X1 U55 ( .A(n61), .B(n67), .C(n64), .Y(n66) );
  OAI21X1 U56 ( .A(count_out[1]), .B(n68), .C(n60), .Y(n64) );
  AOI21X1 U57 ( .A(n54), .B(n61), .C(n55), .Y(n60) );
  INVX1 U58 ( .A(count_out[0]), .Y(n54) );
  NAND2X1 U59 ( .A(n63), .B(count_out[2]), .Y(n65) );
  INVX1 U60 ( .A(n69), .Y(n63) );
  NAND3X1 U61 ( .A(count_out[1]), .B(count_out[0]), .C(n61), .Y(n69) );
  OAI21X1 U62 ( .A(n70), .B(n71), .C(n72), .Y(n48) );
  NAND2X1 U63 ( .A(rollover_flag), .B(n55), .Y(n72) );
  NAND3X1 U64 ( .A(n73), .B(n61), .C(n74), .Y(n71) );
  MUX2X1 U65 ( .B(n75), .A(n76), .S(n77), .Y(n74) );
  NOR2X1 U66 ( .A(rollover_val[3]), .B(rollover_val[2]), .Y(n76) );
  OAI21X1 U67 ( .A(rollover_val[0]), .B(n78), .C(n79), .Y(n75) );
  INVX1 U68 ( .A(n68), .Y(n61) );
  NAND3X1 U69 ( .A(n80), .B(n57), .C(n58), .Y(n68) );
  NAND3X1 U70 ( .A(n81), .B(n79), .C(n82), .Y(n58) );
  AOI21X1 U71 ( .A(rollover_val[1]), .B(n78), .C(n83), .Y(n82) );
  INVX1 U72 ( .A(n84), .Y(n79) );
  OAI21X1 U73 ( .A(rollover_val[1]), .B(n78), .C(n85), .Y(n84) );
  XNOR2X1 U74 ( .A(count_out[3]), .B(rollover_val[3]), .Y(n81) );
  INVX1 U75 ( .A(clear), .Y(n57) );
  INVX1 U76 ( .A(n55), .Y(n80) );
  NOR2X1 U77 ( .A(count_enable), .B(clear), .Y(n55) );
  XOR2X1 U78 ( .A(n86), .B(count_out[3]), .Y(n73) );
  OAI21X1 U79 ( .A(rollover_val[2]), .B(n87), .C(rollover_val[3]), .Y(n86) );
  INVX1 U80 ( .A(n77), .Y(n87) );
  NAND3X1 U81 ( .A(n83), .B(n88), .C(n89), .Y(n70) );
  OAI21X1 U82 ( .A(n85), .B(n78), .C(n77), .Y(n89) );
  NOR2X1 U83 ( .A(rollover_val[0]), .B(rollover_val[1]), .Y(n77) );
  XOR2X1 U84 ( .A(n67), .B(rollover_val[2]), .Y(n85) );
  INVX1 U85 ( .A(count_out[2]), .Y(n67) );
  NAND3X1 U86 ( .A(rollover_val[1]), .B(n78), .C(rollover_val[0]), .Y(n88) );
  INVX1 U87 ( .A(count_out[1]), .Y(n78) );
  XOR2X1 U88 ( .A(rollover_val[0]), .B(count_out[0]), .Y(n83) );
endmodule

