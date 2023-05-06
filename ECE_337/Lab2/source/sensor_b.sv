// $Id: $
// File name:   sensor_b.sv
// Created:     1/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: behavioral sensor verilog
module sensor_b
(
    input logic [3:0] sensors,
    output logic error
);

    always @(sensors) begin
        error = sensors[0] | (sensors[2] & sensors[1]) | (sensors[3] & sensors[1]);
    end

endmodule