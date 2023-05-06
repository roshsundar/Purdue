// $Id: $
// File name:   rcu.sv
// Created:     2/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: This block is the portion of the design that dictates the current mode of operation for the Receiver Block of the UART.

module rcu
(
    input logic clk, n_rst, new_packet_detected, packet_done, framing_error,
    output logic sbc_clear, sbc_enable, load_buffer, enable_timer
);
    typedef enum logic [2:0] {IDLE, CLEAR_SBC, WAIT_PACK, EN_SBC, WAIT_ERROR, LOAD} state_type;
    state_type state, nxt_state;

    always_ff @( posedge clk, negedge n_rst ) begin : StateReg
        if (n_rst == 0)
            state <= IDLE;
        else
            state <= nxt_state;
    end

    always_comb begin : NXT_LOGIC
        // Set the default value(s)
        nxt_state = state;
        enable_timer = 0;
        sbc_clear = 0;
        sbc_enable = 0;
        load_buffer = 0;

        // Define the override/special case conditions
        case(state)
            IDLE: begin
                nxt_state = (new_packet_detected == 1) ? CLEAR_SBC : IDLE;
            end
            CLEAR_SBC: begin
                sbc_clear = 1;
                nxt_state = WAIT_PACK;
            end
            WAIT_PACK: begin
                enable_timer = 1;
                nxt_state = (packet_done == 1) ? EN_SBC : WAIT_PACK;
            end
            EN_SBC: begin
                sbc_enable = 1;
                nxt_state = WAIT_ERROR;
            end
            WAIT_ERROR: begin
                nxt_state = (framing_error == 0) ? LOAD : IDLE;
            end
            LOAD: begin
                load_buffer = 1;
                nxt_state = IDLE;
            end
        endcase
    end
endmodule