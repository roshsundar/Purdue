// $Id: $
// File name:   moore.sv
// Created:     2/15/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: moore machine 1101 detector
module moore (
    input logic clk, n_rst, i,
    output logic o
);
    typedef enum logic [2:0] {WAITING, RCV1, RCV11, RCV110, RCV1101} state_type;
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
                nxt_state = (i == 1) ? RCV1 : WAITING;
            end
            RCV1: begin
                nxt_state = (i == 1) ? RCV11 : WAITING;
            end
            RCV11: begin
                nxt_state = (i == 0) ? RCV110 : RCV11;
            end
            RCV110: begin
                nxt_state = (i == 1) ? RCV1101 : WAITING;
            end
            RCV1101: begin
                nxt_state = (i == 1) ? RCV11 : WAITING;
                o = 1;
            end
        endcase
    end
endmodule