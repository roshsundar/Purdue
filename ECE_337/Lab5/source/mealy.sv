// $Id: $
// File name:   mealy.sv
// Created:     2/15/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: mealy machine 1101 detector

module mealy (
    input logic clk, n_rst, i,
    output logic o
);
    typedef enum logic [1:0] {WAITING, RCV1, RCV11, RCV110} state_type;
    state_type state, nxt_state;

    always_ff @( posedge clk, negedge n_rst ) begin : StateReg
        if (n_rst == 0)
            state <= WAITING;
        else
            state <= nxt_state;
    end

    always_comb begin : NXT_LOGIC
        // Set the default value(s)
        nxt_state = state;
        o = 0;

        // Define the override/special case conditions
        case(state)
            WAITING: begin
                if (i == 1) begin
                    o = 0;
                    nxt_state = RCV1;
                end
                else begin
                    o = 0;
                    nxt_state = WAITING;
                end
            end
            RCV1: begin
                if (i == 1) begin
                    o = 0;
                    nxt_state = RCV11;
                end
                else begin
                    o = 0;
                    nxt_state = WAITING;
                end
            end
            RCV11: begin
                if (i == 0) begin
                    o = 0;
                    nxt_state = RCV110;
                end
                else begin
                    o = 0;
                    nxt_state = RCV11;
                end
            end
            RCV110: begin
                if (i == 0) begin
                    o = 0;
                    nxt_state = WAITING;
                end
                else begin
                    o = 1;
                    nxt_state = RCV1;
                end
            end
        endcase
    end
endmodule