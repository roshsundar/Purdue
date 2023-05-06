// $Id: $
// File name:   eop_detect.sv
// Created:     4/17/2023
// Author:      Roshan Sundar
// Lab Section: 8
// Version:     1.0  Initial Design Entry
// Description: Detects EOP

module eop_detect (
    input logic d_plus_sync, d_minus_sync,
    output logic eop
);
    assign eop = (d_plus_sync == 0) && (d_minus_sync == 0);
endmodule