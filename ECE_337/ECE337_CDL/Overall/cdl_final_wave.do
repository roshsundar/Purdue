onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider {TB SIGNALS}
add wave -noupdate /tb_overall_cdl/DUT/clk
add wave -noupdate /tb_overall_cdl/DUT/n_rst
add wave -noupdate /tb_overall_cdl/tb_test_case
add wave -noupdate /tb_overall_cdl/tb_test_case_num
add wave -noupdate -divider {AHB SIGNALS}
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/haddr
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/hwdata
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/hsel
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/hsize
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/hwrite
add wave -noupdate -expand -group input -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/AHB/htrans
add wave -noupdate -expand -group Output /tb_overall_cdl/DUT/AHB/hready
add wave -noupdate -expand -group Output /tb_overall_cdl/DUT/AHB/hresp
add wave -noupdate -expand -group Output /tb_overall_cdl/DUT/AHB/hrdata
add wave -noupdate -expand -group Output /tb_overall_cdl/DUT/AHB/d_mode
add wave -noupdate -expand -group {TX and FIFO signals} /tb_overall_cdl/DUT/AHB/tx_packet
add wave -noupdate -expand -group {TX and FIFO signals} /tb_overall_cdl/DUT/AHB/tx_data
add wave -noupdate -divider {FIFO SIGNALS}
add wave -noupdate -group {Enable Signals} /tb_overall_cdl/DUT/FIFO/store
add wave -noupdate -group {Enable Signals} /tb_overall_cdl/DUT/FIFO/get
add wave -noupdate -group {Data and Buffer} /tb_overall_cdl/DUT/FIFO/rdata
add wave -noupdate -group {Data and Buffer} /tb_overall_cdl/DUT/FIFO/buffer_occupancy
add wave -noupdate -divider {RX SIGNALS}
add wave -noupdate -expand -group {RX input} -color {Medium Spring Green} -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/RX/d_plus
add wave -noupdate -expand -group {RX input} -color {Medium Spring Green} -itemcolor {Medium Spring Green} /tb_overall_cdl/DUT/RX/d_minus
add wave -noupdate -group {rx trigger} /tb_overall_cdl/DUT/RX/data_ready
add wave -noupdate -group {rx trigger} /tb_overall_cdl/DUT/RX/error
add wave -noupdate -group {rx trigger} /tb_overall_cdl/DUT/RX/store
add wave -noupdate -divider {TX SIGNALS}
add wave -noupdate -group {tx trigger} /tb_overall_cdl/DUT/TX/get_tx_packet_data
add wave -noupdate -group {tx trigger} /tb_overall_cdl/DUT/TX/tx_transfer_active
add wave -noupdate -group {tx trigger} /tb_overall_cdl/DUT/TX/tx_transfer_error
add wave -noupdate -group {TX output} -color Yellow /tb_overall_cdl/DUT/TX/dplus
add wave -noupdate -group {TX output} -color Yellow /tb_overall_cdl/DUT/TX/dminus
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {290 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {2053 ps}
