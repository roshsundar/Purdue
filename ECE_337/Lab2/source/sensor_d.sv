// $Id: $
// File name:   sensor_d.sv
// Created:     1/20/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: dataflow sensor design
module sensor_d
(
    input wire [3:0] sensors,
    output wire error
);

    assign error = sensors[0] | (sensors[2] & sensors[1]) | (sensors[3] & sensors[1]);

endmodule