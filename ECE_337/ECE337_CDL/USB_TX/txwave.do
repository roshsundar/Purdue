onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider {TB Signals}
add wave -noupdate /tb_wrapper/DUT/clk
add wave -noupdate /tb_wrapper/DUT/n_rst
add wave -noupdate -divider {FIFO Signals}
add wave -noupdate /tb_wrapper/DUT/buffer_occupancy
add wave -noupdate /tb_wrapper/DUT/wdata
add wave -noupdate /tb_wrapper/DUT/get
add wave -noupdate /tb_wrapper/DUT/store
add wave -noupdate -divider {TX Signals}
add wave -noupdate -expand -group input /tb_wrapper/DUT/tx_packet
add wave -noupdate -expand -group input /tb_wrapper/DUT/tx_packet_data
add wave -noupdate /tb_wrapper/DUT/txmodule/controller/state
add wave -noupdate -expand -group output /tb_wrapper/DUT/get_tx_packet_data
add wave -noupdate -expand -group output -color {Orange Red} /tb_wrapper/DUT/tx_transer_active
add wave -noupdate -expand -group output -color {Orange Red} /tb_wrapper/DUT/tx_transfer_error
add wave -noupdate -expand -group output -color {Medium Spring Green} /tb_wrapper/DUT/dminus
add wave -noupdate -expand -group output -color {Medium Spring Green} /tb_wrapper/DUT/dplus
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {7020100 ps} 0}
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
WaveRestoreZoom {0 ps} {33636848 ps}
