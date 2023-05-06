module fifousb (
    input logic clk,
    input logic n_rst,
    input logic store, //write enable
    input logic get, //read enable
    input logic clear, //clear and flush
    input logic [7:0] wdata,
    output logic [7:0] rdata,
    output logic [6:0] buffer_occupancy
);

logic write_full, read_empty;
logic [4:0] write_pointer, read_pointer, nx_write_pointer, nx_read_pointer;
logic [63:0] [7:0] fifo_reg, nx_fifo_reg;
logic [63:0] decoder_out;
integer i;

logic [7:0] nxrdata;

always_ff @(posedge clk, negedge n_rst) begin : REGISTERS
    if (n_rst == 1'b0) begin
        write_pointer <= 5'd0;
        read_pointer <= 5'b0;
        fifo_reg <= 0;
        rdata <= 0;
    end
    else begin
        write_pointer <= nx_write_pointer;
        read_pointer <= nx_read_pointer;
        fifo_reg <= nx_fifo_reg;
        rdata <= nxrdata;
    end
end

assign write_full = ((write_pointer == 5'd63) && (store) && !(get));
assign read_empty = (read_pointer == write_pointer);
assign nxrdata = fifo_reg[read_pointer][7:0]; //mux
assign buffer_occupancy = write_pointer - read_pointer;

always_comb begin : WRITE_CONTROLLER
    if (clear)   
        nx_write_pointer = 5'd0;
    else if ((store && !(write_full)))
        nx_write_pointer = write_pointer + 5'd1;
    else
        nx_write_pointer = write_pointer;
end

always_comb begin : READ_CONTROLLER
    if (clear)   
        nx_read_pointer = 5'd0;
    else if ((get && !(read_empty)))
        nx_read_pointer = read_pointer + 5'd1;
    else
        nx_read_pointer = read_pointer;
end

always_comb begin : FIFO_RAM
    for (i = 0; i < 63; i++) begin //decoder
        decoder_out[i] = (write_pointer == i) ? (store && !(write_full)) : 0;
    end
    
    for (i = 0; i < 63; i++) begin //64x8 registers
        nx_fifo_reg[i][7:0] = (decoder_out[i]) ? wdata : fifo_reg[i][7:0];
    end
end

endmodule