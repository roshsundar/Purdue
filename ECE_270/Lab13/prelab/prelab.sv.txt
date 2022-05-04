module ha (
  input a, b,
  output s, co
);
  assign s = a ^ b;
  assign co = a & b;
endmodule

module faha (
  input a, b, ci,
  output s, co
);
  logic h1_s, h1_co, h2_co;
  ha h1(.a(a), .b(b), .s(h1_s), .co(h1_co));
  ha h2(.a(ci), .b(h1_s), .s(s), .co(h2_co));
  
  assign co = h1_co | h2_co;
endmodule

module fa (
  input a, b, ci,
  output s, co
);

  assign s = a ^ b ^ ci;
  assign co = (a & b) | (a & ci) | (b & ci);
  
endmodule

module fa4 (
  input [3:0] a, b, 
  input ci,
  output [3:0] s, 
  output co
);

  logic f0co, f1co, f2co;
  
  fa f0(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]), .co(f0co));
  fa f1(.a(a[1]), .b(b[1]), .ci(f0co), .s(s[1]), .co(f1co));
  fa f2(.a(a[2]), .b(b[2]), .ci(f1co), .s(s[2]), .co(f2co));
  fa f3(.a(a[3]), .b(b[3]), .ci(f2co), .s(s[3]), .co(co));
  
endmodule

module bcdadd1 (
  input [3:0] a, b, 
  input ci,
  output [3:0] s, 
  output co
);
  logic [3:0] s1;
  logic co1;
  fa4 f1(.a(a), .b(b), .ci(ci), .s(s1), .co(co1));
  
  logic co2;
  assign co2 = (co1) | (s[3] & s[2]) | (s[3] & s[1]);
  logic [3:0] a2;
  assign a2 = {0, co2, co2, 0};
  fa4 f2(.a(a2), .b(s1), .ci(0), .s(s), .co());
  assign co = co2;
  
endmodule

module bcdadd4 (
  input [15:0] a, b, 
  input ci,
  output [15:0] s, 
  output co
);
  logic f0co, f1co, f2co; 
  bcdadd1 ba0(.a(a[3:0]), .b(b[3:0]), .ci(ci), .co(f0co), .s(s[3:0]));
  bcdadd1 ba1(.a(a[7:4]), .b(b[7:4]), .ci(f0co), .co(f1co), .s(s[7:4]));
  bcdadd1 ba2(.a(a[11:8]), .b(b[11:8]), .ci(f1co), .co(f2co), .s(s[11:8]));
  bcdadd1 ba3(.a(a[15:12]), .b(b[15:12]), .ci(f2co), .co(co), .s(s[15:12]));
endmodule

module bcd9comp1 (
  input [3:0] in,
  output logic [3:0] out
);
  always_comb begin
  case(in)
    4'b0000: out = 4'b1001;
    4'b0001: out = 4'b1000;
    4'b0010: out = 4'b0111;
    4'b0011: out = 4'b0110;
    4'b0100: out = 4'b0101;
    4'b0101: out = 4'b0100;
    4'b0110: out = 4'b0011;
    4'b0111: out = 4'b0010;
    4'b1000: out = 4'b0001;
    4'b1001: out = 4'b0000;
    default: out = 4'b0000;
  endcase   
  end
endmodule


module bcdaddsub4 (
  input [15:0] a, b,
  input op,
  output [15:0] s,
);
  logic [15:0] l;
  bcd9comp1 cmp0(.in(b[3:0]), .out(l[3:0]));
  bcd9comp1 cmp1(.in(b[7:4]), .out(l[7:4]));
  bcd9comp1 cmp2(.in(b[11:8]), .out(l[11:8]));
  bcd9comp1 cmp3(.in(b[15:12]), .out(l[15:12]));
  
  logic [15:0] c;
  always_comb
  begin
    if (op == 1) begin
      c = l;
    end
    else begin
      c = b;
    end
  end
  
  bcdadd4 ba1(.a(a), .b(c), .ci(op), .s(s));
endmodule