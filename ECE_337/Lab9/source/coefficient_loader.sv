// $Id: $
// File name:   coefficient_loader.sv
// Created:     3/24/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: loads a full set of coefficients from the AHB-Lite interface module into the FIR Filter module.

module coefficient_loader(
    input logic clk, n_reset,
    input logic new_coefficient_set, modwait,
    output logic load_coeff,
    output logic [1:0] coefficient_num
);
    typedef enum logic [1:0] {IDLE, SEND, WAIT} state_type;
    state_type state, nxt_state;

    logic [1:0] nxt_coeff_num;

    always_ff @( posedge clk, negedge n_reset ) begin : StateReg
        if (n_reset == 0) begin
            state <= IDLE;
            coefficient_num <= 0;
        end
        else begin
            state <= nxt_state;
            coefficient_num <= nxt_coeff_num;
        end
    end

    always_comb begin : NXT_LOGIC
        load_coeff = 0;
        nxt_state = state;
        nxt_coeff_num = coefficient_num;

        case(state)
            IDLE:
                nxt_state = (new_coefficient_set == 1) ? SEND : IDLE;
            SEND: begin
                load_coeff = 1;
                nxt_state = (modwait == 1) ? WAIT : SEND;
            end
            WAIT: begin
                nxt_coeff_num = coefficient_num + 1;
                if (coefficient_num == 3 && modwait == 0)
                    nxt_state = IDLE;
                else if (modwait == 0)
                    nxt_state = SEND;
                else
                    nxt_state = WAIT;
            end
        endcase
    end
endmodule