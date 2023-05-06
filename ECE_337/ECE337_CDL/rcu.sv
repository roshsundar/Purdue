// $Id: $
// File name:   rcu.sv
// Created:     4/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Controller for USB RX module

module rcu (
    input logic clk, n_rst,
    input logic d_edge, byte_rcvd, eop, shift_en,
    input logic [6:0] buffer_occ,
    input logic [7:0] rcv_byte,
    output logic flush, store, rcving, data_ready, error,
    output logic [2:0] pid,
    output logic [7:0] prev_byte
);
    typedef enum logic [4:0] {IDLE, FLUSH, RCV_SYNC, CHK_SYNC, SYNC_ERR, RCV_PID, CHK_PID, PID_ERR, 
                                RCV_TOK1, RCV_TOK2, DONE, WAIT_INIT, WRITE_INIT, WAIT, DATA_ERR, WRITE, DATA_RCVD} state_type;
    state_type state, nxt_state;

    logic reg_rcv; logic [7:0] nxt_prev;

    always_ff @( posedge clk, negedge n_rst ) begin : StateReg
        if (n_rst == 0) begin
            state <= IDLE;
            prev_byte <= '1;
        end
        else begin
            state <= nxt_state;
            prev_byte <= (reg_rcv == 1) ? nxt_prev : prev_byte;
        end
    end

    always_comb begin : NXT_LOGIC
        nxt_state = state;
        nxt_prev = '1;
        flush = 0; store = 0; reg_rcv = 0; rcving = 0; data_ready = 0; error = 0;
        pid = 3'b0;

        case(state)
            IDLE:
                nxt_state = (d_edge == 1) ? FLUSH : IDLE;
            FLUSH: begin
                flush = 1; rcving = 1;
                nxt_state = RCV_SYNC;
            end
            RCV_SYNC: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  CHK_SYNC : RCV_SYNC;
            end
            CHK_SYNC: begin
                rcving = 1;
                nxt_state = (rcv_byte == 8'b10000000) ?  RCV_PID : SYNC_ERR;
            end
            SYNC_ERR: begin
                error = 1; rcving = 1;
                nxt_state = (eop == 1) ? IDLE : SYNC_ERR;
            end
            RCV_PID: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  CHK_PID : RCV_PID;
            end
            CHK_PID: begin
                // lower 4 bits of rcv_byte are PID
                rcving = 1;
                case (rcv_byte[3:0])
                    4'b0001: begin // OUT
                        pid = 3'd0; 
                        nxt_state = RCV_TOK1;
                    end
                    4'b1001: begin // IN
                        pid = 3'd1;
                        nxt_state = RCV_TOK1;
                    end
                    4'b0011: begin // DATA0
                        pid = 3'd2;
                        nxt_state = WAIT_INIT;
                    end
                    4'b1011: begin // DATA1
                        pid = 3'd3;
                        nxt_state = WAIT_INIT;
                    end
                    4'b0010: begin // ACK
                        pid = 3'd4;
                        nxt_state = DONE;
                    end
                    4'b1010: begin // NACK
                        pid = 3'd5;
                        nxt_state = DONE;
                    end
                    default: nxt_state = PID_ERR; // No valid PID
                endcase
            end
            PID_ERR: begin
                error = 1; rcving = 1;
                nxt_state = (eop == 1) ? IDLE : PID_ERR;
            end
            RCV_TOK1: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  RCV_TOK2 : RCV_TOK1;
            end
            RCV_TOK2: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  DONE : RCV_TOK2;
            end
            DONE: // rcving = 0
                nxt_state = IDLE;
            WAIT_INIT: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  WRITE_INIT : ((eop == 1) ? DATA_ERR : WAIT_INIT);
            end
            WRITE_INIT: begin
                rcving = 1;
                reg_rcv = 1; nxt_prev = rcv_byte;
                nxt_state = WAIT;
            end
            WAIT: begin
                rcving = 1;
                nxt_state = (byte_rcvd == 1) ?  WRITE : ((eop == 1) ? DATA_ERR : WAIT);
            end
            WRITE: begin
                rcving = 1;
                if (shift_en) begin
                    if (eop)
                        nxt_state = DATA_RCVD;
                    else begin
                        nxt_state = WAIT;
                        reg_rcv = 1; nxt_prev = rcv_byte;
                        if (buffer_occ < 7'd64)
                            store = 1;
                    end
                end
                else
                    nxt_state = WRITE;
            end
            DATA_RCVD: begin
                data_ready = 1;
                nxt_state = IDLE;
            end
            DATA_ERR: begin
                error = 1; rcving = 1;
                nxt_state = (eop == 1) ? IDLE : DATA_ERR;
            end
        endcase
    end
endmodule