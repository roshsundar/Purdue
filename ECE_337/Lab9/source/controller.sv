// $Id: $
// File name:   controller.sv
// Created:     2/28/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: control unit for FIR convolution.

module controller
(
    input logic clk, n_rst, dr, lc, overflow,
    output logic cnt_up, clear, modwait, 
    output logic [2:0] op,
    output logic [3:0] src1,
    output logic [3:0] src2,
    output logic [3:0] dest,
    output logic err
);
    typedef enum logic [2:0] {NOP = 3'b000, COPY = 3'b001, LOAD1 = 3'b010, LOAD2 = 3'b011, ADD = 3'b100, SUB = 3'b101, MUL = 3'b110} op_type;

    typedef enum logic [4:0] {IDLE, STORE, ZERO, SHIFT1, SHIFT2, SHIFT3, SHIFT4, MUL1, ADD1, MUL2, SUB2, MUL3, ADD3, MUL4, SUB4,
                                LOAD_F0, WAIT_FO, LOAD_F1, WAIT_F1, LOAD_F2, WAIT_F2, LOAD_F3, WAIT_F3, EIDLE} state_type;
    state_type state, nxt_state;
    logic nxt_modwait;

    always_ff @( posedge clk, negedge n_rst ) begin : StateReg
        if (n_rst == 0) begin
            state <= IDLE;
            modwait <= 0;
        end
        else begin
            state <= nxt_state;
            modwait <= nxt_modwait;
        end
    end

    always_comb begin : NXT_LOGIC
        // Set the default value(s)
        nxt_state = state;
        op = NOP;
        src1 = 0;
        src2 = 0;
        dest = 0;
        nxt_modwait = 0;
        err = 0;
        cnt_up = 0;
        clear = 0;

        // Define the override/special case conditions
        case(state)
            EIDLE: begin
                err = 1;

                if (lc == 1) begin
                    nxt_state = LOAD_F0;
                    nxt_modwait = 1;
                end
                else if (dr == 1) begin
                    nxt_state = STORE;
                    nxt_modwait = 1;
                end
                else if (dr == 0)
                    nxt_state = EIDLE;
            end
            IDLE: begin
                if (lc == 1) begin
                    nxt_state = LOAD_F0;
                    nxt_modwait = 1;
                end
                else if (dr == 1) begin
                    nxt_state = STORE;
                    nxt_modwait = 1;
                end
                else if (dr == 0)
                    nxt_state = IDLE;
            end
            STORE: begin
                op = LOAD1;
                dest = 4'd5;
                nxt_modwait = 1;

                nxt_state = (dr == 1) ? ZERO : EIDLE;
            end
            ZERO: begin
                op = SUB;
                src1 = 0;
                src2 = 0;
                dest = 0;
                cnt_up = 1;
                nxt_modwait = 1;

                nxt_state = SHIFT1;
            end
            SHIFT1: begin
                op = COPY;
                src1 = 4'd2;
                dest = 4'd1;
                nxt_modwait = 1;

                nxt_state = SHIFT2;
            end
            SHIFT2: begin
                op = COPY;
                src1 = 4'd3;
                dest = 4'd2;
                nxt_modwait = 1;

                nxt_state = SHIFT3;
            end
            SHIFT3: begin
                op = COPY;
                src1 = 4'd4;
                dest = 4'd3;
                nxt_modwait = 1;

                nxt_state = SHIFT4;
            end
            SHIFT4: begin
                op = COPY;
                src1 = 4'd5;
                dest = 4'd4;
                nxt_modwait = 1;

                nxt_state = MUL1;
            end
            MUL1: begin
                op = MUL;
                src1 = 4'd1;
                src2 = 4'd7;
                dest= 4'd6;
                nxt_modwait = 1;

                nxt_state = ADD1;
            end
            ADD1: begin
                op = ADD;
                src1 = 0;
                src2 = 4'd6;
                dest = 0;
                nxt_modwait = 1;

                nxt_state = (overflow == 1) ? EIDLE : MUL2;
            end
            MUL2: begin
                op = MUL;
                src1 = 4'd2;
                src2 = 4'd8;
                dest= 4'd6;
                nxt_modwait = 1;

                nxt_state = SUB2;
            end
            SUB2: begin
                op = SUB;
                src1 = 0;
                src2 = 4'd6;
                dest = 0;
                nxt_modwait = 1;

                nxt_state = (overflow == 1) ? EIDLE : MUL3;
            end
            MUL3: begin
                op = MUL;
                src1 = 4'd3;
                src2 = 4'd9;
                dest= 4'd6;
                nxt_modwait = 1;

                nxt_state = ADD3;
            end
            ADD3: begin
                op = ADD;
                src1 = 0;
                src2 = 4'd6;
                dest = 0;
                nxt_modwait = 1;

                nxt_state = (overflow == 1) ? EIDLE : MUL4;
            end
            MUL4: begin
                op = MUL;
                src1 = 4'd4;
                src2 = 4'd10;
                dest= 4'd6;
                nxt_modwait = 1;

                nxt_state = SUB4;
            end
            SUB4: begin
                op = SUB;
                src1 = 0;
                src2 = 4'd6;
                dest = 0;

                nxt_state = (overflow == 1) ? EIDLE : IDLE;
            end
            LOAD_F0: begin
                op = LOAD2;
                dest = 4'd10;
                clear = 1;

                nxt_state = WAIT_FO;
            end
            WAIT_FO: begin
                clear = 1;

                if (lc == 1) begin
                    nxt_state = LOAD_F1;
                    nxt_modwait = 1;
                end
                else
                    nxt_state = WAIT_FO;
            end
            LOAD_F1: begin
                op = LOAD2;
                dest = 4'd9;
                clear = 1;

                nxt_state = WAIT_F1;
            end
            WAIT_F1: begin
                clear = 1;
                
                if (lc == 1) begin
                    nxt_state = LOAD_F2;
                    nxt_modwait = 1;
                end
                else
                    nxt_state = WAIT_F1;
            end
            LOAD_F2: begin
                op = LOAD2;
                dest = 4'd8;
                clear = 1;

                nxt_state = WAIT_F2;
            end
            WAIT_F2: begin
                clear = 1;
                
                if (lc == 1) begin
                    nxt_state = LOAD_F3;
                    nxt_modwait = 1;
                end
                else
                    nxt_state = WAIT_F2;
            end
            LOAD_F3: begin
                op = LOAD2;
                dest = 4'd7;
                clear = 1;

                nxt_state = IDLE;
            end
        endcase
    end
endmodule