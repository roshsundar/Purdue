# ECE337 CDL

Team Members: Roshan Sundar, Harim Choe, Tristan Marta

This is the GitHub repository documenting all codes used for the Purdue ECE 337 CDL.

We are going to design and verify a USB Full-Speed Bulk-Transfer Endpoint AHB-Lite SoC Module. 

Resources such as the manual and the RTL diagrams can be found in the (/Docs) folder

All other SystemVerilog modules for AHB-lite Slave, USB RX, USB TX, FIFO, and the overall wrapper module can be found in this repository. Test benches for all modules except for the FIFO buffer will be present here as well. Our design is based on the RTL diagrams we made and the test benches are based on the different test cases we specified in the design documents.

Ideally, our design should be able to these transfers:

Host-to-Endpoint Transfers:
1. The SoC core would periodically check the status register to see if a Host-to-Endpoint Token has been received.
2. The SoC core would then make sure the Data Buffer was empty and ready to receive a data packet.
3. The SoC core would then periodically check the status register to see if new data had arrived from a data packet.
4. Once data has been received from the Host, the SoC core will tell the design to send an ’ACK’.
5. The SoC core will check the buffer occupancy register to find out how much data was received.
6. The SoC core will then retrieve the data via a sequence of reads.
7. Once all of the data has been retrieved from the buffer, the data-available flag in the status register must be cleared by the design.

Endpoint-to-Host Transfers:
1. The SoC core will make sure the data buffer is currently empty.
2. The SoC core will populate the data buffer with the data to send via a sequence of writes.
3. Once the data buffer currently holds as much data as set for the data payload size, the SoC core will tell the design to send a data packet.
4. The SoC core will periodically check to see when the data packet sending finishes.
5. The SoC core will periodically check that an ’ACK’ was received, and perform any error handling if another packet type is seen first.

The description explaned above is shown in section 4.3 in the lab manual.
