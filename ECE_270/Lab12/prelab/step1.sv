module count8du (
  input clk, rst, enable,
  output[7:0] out
);

  logic [7:0] Q, next_Q;
  assign out = Q;

  always_ff @(posedge clk, posedge rst)
  begin
    if (rst == 1) begin
      Q <= 8'd0;
    end
    else if (enable == 1)
    begin
      if (Q == 8'd99) begin
        Q <= 8'd0;
      end
      else begin
        Q <= next_Q;
      end
    end
  end
  
  always_comb
  begin
    next_Q = Q + 1;
  end

endmodule