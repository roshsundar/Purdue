module usb_ahb_lite_slave (
    input logic clk,
    input logic n_rst,

    // RX Data Signals
    input logic [2:0] rx_packet,
    input logic rx_data_ready,
    input logic rx_transfer_active,
    input logic rx_error,

    // FIFO Signals
    input logic [6:0] buffer_occupancy,
    input logic [7:0] rx_data,
    output logic get_rx_data,
    output logic store_rx_data,
    output logic [7:0] tx_data,
    output logic clear,

    // TX Data Signals
    output logic [1:0] tx_packet,
    input logic tx_transfer_active,
    input logic tx_error,

    // Master Signals
    input logic hsel,
    input logic [3:0] haddr,
    input logic [1:0] hsize,
    input logic [1:0] htrans,
    input logic hwrite,
    input logic [31:0] hwdata,
    output logic [31:0] hrdata,
    output logic hresp,
    output logic hready,

    // D Mode
    output logic d_mode
);

    // Address Decoder
    logic [3:0] decoded_addr;
    assign decoded_addr = haddr;

    // RDATA Register
    logic [31:0] rdata_reg;
    assign hrdata = rdata_reg;

    // Value Registers
    logic [31:0] value_regs [13:0]; // 14 registers
    logic get_rx_data_reg, store_rx_data_reg, clear_reg;
    logic [7:0] tx_data_reg;
    logic [1:0] tx_packet_reg;
    logic d_mode_reg;

    always_ff @(posedge clk or negedge n_rst) begin
        if (!n_rst) begin
            get_rx_data_reg <= 1'b0;
            store_rx_data_reg <= 1'b0;
            clear_reg <= 1'b0;
            tx_data <= 8'b0;
            tx_packet_reg <= 2'b0;
            d_mode_reg <= 1'b0;
        end else begin
            get_rx_data_reg <= get_rx_data;
            store_rx_data_reg <= store_rx_data;
            clear_reg <= clear;
            tx_data <= tx_data_reg;
            tx_packet_reg <= tx_packet;
            d_mode_reg <= d_mode;
        end
    end

    // Address Mapping and Access Control
    always_ff @(posedge clk) begin
        if (hsel && hready) begin
            hresp <= 1'b0;
            case (decoded_addr)
                4'b0000: begin
                    if (hwrite) begin
                        value_regs[0] <= (hsize == 2'b11) ? hwdata : (hsize == 2'b10) ? {value_regs[0][15:8], hwdata[7:0]} : {value_regs[0][23:16], hwdata[15:8]};
                        store_rx_data <= 1'b1;
                        tx_data <= hwdata[7:0];
                    end else begin
                        get_rx_data <= 1'b1;
                        rdata_reg <= value_regs[0];
                    end
                end

                4'b0100: if (!hwrite) rdata_reg <= value_regs[4];

                4'b0110: if (!hwrite) rdata_reg <= value_regs[6];

                               4'b1000: if (!hwrite) rdata_reg <= value_regs[8];

                4'b1100: begin
                    if (hwrite) begin
                        value_regs[12] <= (hsize == 2'b00) ? {value_regs[12][7:0], hwdata[7:0]} : hwdata[15:0];
                        tx_packet <= hwdata[1:0];
                    end else begin
                        rdata_reg <= value_regs[12];
                    end
                end

                4'b1101: begin
                    if (hwrite) begin
                        value_regs[13] <= (hsize == 2'b00) ? {value_regs[13][7:0], hwdata[7:0]} : hwdata[15:0];
                        clear <= hwdata[0];
                    end else begin
                        rdata_reg <= value_regs[13];
                    end
                end

                default: hresp <= 1'b1; // Error response for invalid addresses
            endcase
        end else begin
            hready <= 1'b1;
        end
    end

    // Update Status and Error Registers
    always_ff @(posedge clk) begin
        value_regs[4] <= {tx_error, tx_transfer_active, rx_error, rx_transfer_active, rx_error, 5'b0, rx_data_ready};
        value_regs[6] <= {tx_error, 7'b0, rx_error};
    end

    // Update Buffer Occupancy
    always_ff @(posedge clk) begin
        value_regs[8][7:0] <= buffer_occupancy;
    end

    // Update D Mode
    always_ff @(posedge clk) begin
        d_mode <= d_mode_reg;
    end

    // Reset control signals
    always_ff @(posedge clk) begin
        if (clear_reg || !n_rst) begin
            get_rx_data <= 1'b0;
            store_rx_data <= 1'b0;
            clear <= 1'b0;
        end
    end
    
endmodule
