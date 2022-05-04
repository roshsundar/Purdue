module fr_counter (
  input clk, rst, enable,
  output[7:0] out
);

  logic [7:0] counter;
  assign out = counter;

  always_ff @(posedge clk, posedge rst)
  begin
    if (rst == 1)
    begin
      counter <= 8'b00000000;
    end
    else if (enable == 1)
    begin
      counter <= counter + 1;
    end
  end

endmodule