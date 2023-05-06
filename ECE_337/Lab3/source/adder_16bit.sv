// 337 TA Provided Lab 2 8-bit adder wrapper file template
// This code serves as a template for the 8-bit adder design wrapper file 
// STUDENT: Replace this message and the above header section with an
// appropriate header based on your other code files

module adder_16bit
(
	input wire [15:0] a,
	input wire [15:0] b,
	input wire carry_in,
	output wire [15:0] sum,
	output wire overflow
);

	// STUDENT: Fill in the correct port map with parameter override syntax for using your n-bit ripple carry adder design to be an 8-bit ripple carry adder design
	always @(a, b, carry_in) begin

		assert ((a >= 16'h0000) && (a <= 16'hffff))
		else $error("Input 'a' exceeds bounds");

		assert ((b >= 16'h0000) && (b <= 16'hffff))
		else $error("Input 'b' exceeds bounds");
	end

	adder_nbit  #(16) NADDER (.a(a), .b(b), .carry_in(carry_in), .sum(sum), .overflow(overflow));
endmodule
