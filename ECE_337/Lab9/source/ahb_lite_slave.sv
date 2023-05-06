// $Id: $
// File name:   ahb_lite_slave.sv
// Created:     3/22/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: AHB-Lite interface for FIR filter.

module ahb_lite_slave (
    input logic clk, n_rst,
    input logic modwait, err, hsel, hsize, hwrite,
    input logic [3:0] haddr,
    input logic [1:0] htrans, coefficient_num,
    input logic [15:0] hwdata, fir_out,
    output logic [15:0] hrdata, sample_data, fir_coefficient,
    output logic hresp, data_ready, new_coefficient_set
);
    logic [15:0] nxt_sample, nxt_F0, F0, nxt_F1, F1, nxt_F2, F2, nxt_F3, F3, nxt_hrdata, status, result;
    logic nxt_ncs, dr, dr1, dr2;
    logic [4:0] writesel, nxt_writesel;

    always_ff @(posedge clk, negedge n_rst) begin
        if (n_rst == 0) begin
            hrdata <= 0;
            result <= 0;
            sample_data <= 0;
            F0 <= 0;
            F1 <= 0;
            F2 <= 0;
            F3 <= 0;
            new_coefficient_set <= 0;
            writesel <= 5'd20;
        end
        else begin
            hrdata <= nxt_hrdata;
            result <= fir_out;
            sample_data <= nxt_sample;
            F0 <= nxt_F0;
            F1 <= nxt_F1;
            F2 <= nxt_F2;
            F3 <= nxt_F3;
            new_coefficient_set <= nxt_ncs;
            writesel <= nxt_writesel;
        end
    end

    always_ff @(posedge clk, negedge n_rst) begin
        if (n_rst == 0) begin
            dr1 <= 0;
            dr2 <= 0;
        end
        else begin
            dr1 <= dr;
            dr2 <= dr1;
        end
    end

    assign data_ready = dr1 || dr2;
    assign status = {7'b0, err, 7'b0, (modwait | new_coefficient_set)};

    always_comb begin
        hresp = 0;
        nxt_hrdata = hrdata;
        nxt_writesel = 5'd20;

        // bus transaction
        if (htrans == 2'd2 && hsel) begin
            // error checks
            if (hwrite && (haddr == 4'h0 || haddr == 4'h1 || haddr == 4'h2 || haddr == 4'h3 || haddr == 4'hF))
                hresp = 1;
            // write
            else if (hwrite) begin
                // write to [sample data] register
                if (hsize && (haddr == 4'h4 || haddr == 4'h5)) begin
                    nxt_writesel = 5'd0;
                end
                else if (haddr == 4'h4) begin
                    nxt_writesel = 5'd1;
                end
                else if (haddr == 4'h5) begin
                    nxt_writesel = 5'd2;
                end

                // write to [F0] register
                if (hsize && (haddr == 4'h6 || haddr == 4'h7))
                    nxt_writesel = 5'd3;
                else if (haddr == 4'h6)
                    nxt_writesel = 5'd4;
                else if (haddr == 4'h7)
                    nxt_writesel = 5'd5;

                // write to [F1] register
                if (hsize && (haddr == 4'h8 || haddr == 4'h9))
                    nxt_writesel = 5'd6;
                else if (haddr == 4'h8)
                    nxt_writesel = 5'd7;
                else if (haddr == 4'h9)
                    nxt_writesel = 5'd8;

                // write to [F2] register
                if (hsize && (haddr == 4'hA || haddr == 4'hB))
                    nxt_writesel = 5'd9;
                else if (haddr == 4'hA)
                    nxt_writesel = 5'd10;
                else if (haddr == 4'hB)
                    nxt_writesel = 5'd11;

                // write to [F3] register
                if (hsize && (haddr == 4'hC || haddr == 4'hD))
                    nxt_writesel = 5'd12;
                else if (haddr == 4'hC)
                    nxt_writesel = 5'd13;
                else if (haddr == 4'hD)
                    nxt_writesel = 5'd14;
                
                // write to [new coefficient set] register
                if (haddr == 4'hE)
                    nxt_writesel = 5'd15;
            end
            // read
            else begin
                // read [status] register
                if (hsize && (haddr == 4'h0 || haddr == 4'h1))
                    nxt_hrdata = status;
                else if (haddr == 4'h0)
                    nxt_hrdata = {8'd0, status[7:0]};
                else if (haddr == 4'h1)
                    nxt_hrdata = {8'd0, status[15:8]};

                // read [result] register
                if (hsize && (haddr == 4'h2 || haddr == 4'h3))
                    nxt_hrdata = result;
                else if (haddr == 4'h2)
                    nxt_hrdata = {8'd0, result[7:0]};
                else if (haddr == 4'h3)
                    nxt_hrdata = {8'd0, result[15:8]};
                
                // read [sample data] register
                if (hsize && (haddr == 4'h4 || haddr == 4'h5))
                    nxt_hrdata = nxt_sample;
                else if (haddr == 4'h4)
                    nxt_hrdata = {8'd0, nxt_sample[7:0]};
                else if (haddr == 4'h5)
                    nxt_hrdata = {8'd0, nxt_sample[15:8]};
                
                // read [F0] register
                if (hsize && (haddr == 4'h6 || haddr == 4'h7))
                    nxt_hrdata = nxt_F0;
                else if (haddr == 4'h6)
                    nxt_hrdata = {8'd0, nxt_F0[7:0]};
                else if (haddr == 4'h7)
                    nxt_hrdata = {8'd0, nxt_F0[15:8]};
                
                // read [F1] register
                if (hsize && (haddr == 4'h8 || haddr == 4'h9))
                    nxt_hrdata = nxt_F1;
                else if (haddr == 4'h8)
                    nxt_hrdata = {8'd0, nxt_F1[7:0]};
                else if (haddr == 4'h9)
                    nxt_hrdata = {8'd0, nxt_F1[15:8]};
                
                // read [F2] register
                if (hsize && (haddr == 4'hA || haddr == 4'hB))
                    nxt_hrdata = nxt_F2;
                else if (haddr == 4'hA)
                    nxt_hrdata = {8'd0, nxt_F2[7:0]};
                else if (haddr == 4'hB)
                    nxt_hrdata = {8'd0, nxt_F2[15:8]};
                
                // read [F3] register
                if (hsize && (haddr == 4'hC || haddr == 4'hD))
                    nxt_hrdata = nxt_F3;
                else if (haddr == 4'hC)
                    nxt_hrdata = {8'd0, nxt_F3[7:0]};
                else if (haddr == 4'hD)
                    nxt_hrdata = {8'd0, nxt_F3[15:8]};
                
                // read [new coefficient set] register
                if (haddr == 4'hE)
                    nxt_hrdata = {15'd0, new_coefficient_set};
            end
        end
    end

    always_comb begin
        dr = 0;
        nxt_sample = sample_data;
        nxt_F0 = F0;
        nxt_F1 = F1;
        nxt_F2 = F2;
        nxt_F3 = F3;
        nxt_ncs = new_coefficient_set;
        
        case(writesel)
            5'd0: begin
                nxt_sample = hwdata;
                dr = 1;
            end
            5'd1: begin
                nxt_sample = {sample_data[15:8], hwdata[7:0]};
                dr = 1;
            end
            5'd2: begin
                nxt_sample = {hwdata[15:8], sample_data[7:0]};
                dr = 1;
            end
            5'd3:   nxt_F0 = hwdata;
            5'd4:   nxt_F0 = {F0[15:8], hwdata[7:0]};
            5'd5:   nxt_F0 = {hwdata[15:8], F0[7:0]};
            5'd6:   nxt_F1 = hwdata;
            5'd7:   nxt_F1 = {F1[15:8], hwdata[7:0]};
            5'd8:   nxt_F1 = {hwdata[15:8], F1[7:0]};
            5'd9:   nxt_F2 = hwdata;
            5'd10:  nxt_F2 = {F2[15:8], hwdata[7:0]};
            5'd11:  nxt_F2 = {hwdata[15:8], F2[7:0]};
            5'd12:  nxt_F3 = hwdata;
            5'd13:  nxt_F3 = {F3[15:8], hwdata[7:0]};
            5'd14:  nxt_F3 = {hwdata[15:8], F3[7:0]};
            5'd15:  nxt_ncs = hwdata[0];
        endcase

        // FIR coefficient select
        if (coefficient_num == 2'd0)
            fir_coefficient = F0;
        else if (coefficient_num == 2'd1)
            fir_coefficient = F1;
        else if (coefficient_num == 2'd2)
            fir_coefficient = F2;
        else if (coefficient_num == 2'd3) begin
            fir_coefficient = F3;
            nxt_ncs = 0; // clear [new coefficient set] register when loading is done
        end
    end
endmodule