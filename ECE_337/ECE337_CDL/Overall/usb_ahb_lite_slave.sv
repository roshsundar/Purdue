module usb_ahb_lite_slave
    (
    //Clock and Negedge Reset
    input logic clk,
    input logic n_rst,

    //RX Data Signals
    input logic [2:0] rx_packet,
    input logic rx_data_ready,
    input logic rx_transfer_active,
    input logic rx_error,

    //FIFO Signals
    input logic [6:0] buffer_occupancy,
    input logic [7:0] rx_data,
    output logic get_rx_data,
    output logic store_rx_data,
    output logic [7:0] tx_data,
    output logic clear,

    //TX Data Signals
    output logic [1:0] tx_packet,
    input logic tx_transfer_active,
    input logic tx_error,

    //Master Signals
    input logic hsel,
    input logic [3:0] haddr,
    input logic [1:0] hsize,
    input logic [1:0] htrans,
    input logic hwrite,
    input logic [31:0] hwdata,
    output logic [31:0] hrdata,
    output logic hresp,
    output logic hready,

    //D Mode
    output logic d_mode
);

    // Internal signals
    reg [15:0] status_reg, nx_status_reg;
    reg [15:0] error_reg, nx_error_reg;
    reg [7:0] tx_packet_ctrl_reg;
    reg flush_buffer_ctrl_reg;
    reg [31:0] data_buffer[0:3];

    // Always_comb block for address mapping
    always_comb begin
        case (haddr[3:0])
            4'h0, 4'h1, 4'h2, 4'h3: hrdata = data_buffer[haddr[1:0]];
            4'h4, 4'h5: hrdata = {16'b0, status_reg};
            4'h6, 4'h7: hrdata = {16'b0, error_reg};
            4'h8: hrdata = {24'b0, buffer_occupancy};
            4'hC: hrdata = {24'b0, tx_packet_ctrl_reg};
            4'hD: hrdata = {24'b0, flush_buffer_ctrl_reg};
            default: hrdata = 32'b0;
        endcase

        // Update status register based on input signals
        nx_status_reg[0] <= rx_packet[0];
        nx_status_reg[1] <= rx_packet[1];
        nx_status_reg[2] <= rx_packet[2];
        nx_status_reg[3] <= rx_data_ready;
        nx_status_reg[4] <= rx_transfer_active;
        nx_status_reg[5] <= rx_error;
        nx_status_reg[15:6] <= 10'b0;

         nx_error_reg[0] <= rx_error;
         nx_error_reg[8] <= tx_error;
         nx_error_reg[15:9] <= 7'b0;
    end

    // Always_ff block for handling writes and updates
    always_ff @(posedge clk or negedge n_rst) begin
        if (!n_rst) begin
            status_reg <= 16'b0;
            error_reg <= 16'b0;
            tx_packet_ctrl_reg <= 8'b0;
            flush_buffer_ctrl_reg <= 1'b0;
            data_buffer[0] <= 0;
            data_buffer[1] <= 0;
            data_buffer[2] <= 0;
            data_buffer[3] <= 0;
        end 
        
        else begin

            case (haddr[3:0])
                4'h0, 4'h1, 4'h2, 4'h3: if ((hsel) && ((htrans == 2'd2) || (htrans == 2'd3)) && (hwrite)) begin
                                            data_buffer[haddr[1:0]] <= hwdata;
                                            store_rx_data <= 1'b1;
                                        end else begin
                                            store_rx_data <= 1'b0;
                                        end
                4'hC: if ((hsel) && ((htrans == 2'd2) || (htrans == 2'd3)) && (hwrite)) begin
                        tx_packet_ctrl_reg <= hwdata[7:0];
                     end
                4'hD: if ((hsel) && ((htrans == 2'd2) || (htrans == 2'd3)) && (hwrite)) begin
                        flush_buffer_ctrl_reg <= hwdata[7:0] & 1'b1;
                     end
            endcase
            
            status_reg <= nx_status_reg;
            error_reg <= nx_error_reg;

            get_rx_data <= (hwrite && hsel && (haddr[3:0] == 4'h0));
            tx_packet <= tx_packet_ctrl_reg[1:0];
            clear <= flush_buffer_ctrl_reg;
        end
        
        // Update status register based on input signals

        /*
        // // Update error register based on input signals
        error_reg[0] <= rx_error;
        error_reg[8] <= tx_error;
        error_reg[15:9] <= 7'b0;

        // Update tx_packet and get_rx_data signals based on control registers
        get_rx_data <= (hwrite && hsel && (haddr[3:0] == 4'h0));
        tx_packet <= tx_packet_ctrl_reg[1:0];
        clear <= flush_buffer_ctrl_reg;
        */

end

// Connect the tx_data to the corresponding data buffer
assign tx_data = data_buffer[0][7:0];

// Connect the hready and hresp signals to appropriate values
assign hready = 1'b1;
assign hresp = 1'b0;

endmodule
