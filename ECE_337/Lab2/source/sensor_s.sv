// $Id: $
// File name:   sensor_s.sv
// Created:     1/19/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: postlab 1 sensor implementation
module sensor_s
(
    input wire [3:0] sensors,
    output wire error
);

    wire s3s1;
    wire s2s1;

    AND2X1 A1 (.Y(s3s1), .A(sensors[3]), .B(sensors[1]));
    AND2X1 A2 (.Y(s2s1), .A(sensors[2]), .B(sensors[1]));

    wire s3s1_or_s2s1;
    OR2X1 O1 (.Y(s3s1_or_s2s1), .A(s3s1), .B(s2s1));

    OR2X1 O2 (.Y(error), .A(s3s1_or_s2s1), .B(sensors[0]));

endmodule