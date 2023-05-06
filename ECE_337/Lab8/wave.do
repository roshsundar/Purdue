onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_apb_slave/tb_clk
add wave -noupdate /tb_apb_slave/tb_n_rst
add wave -noupdate /tb_apb_slave/tb_test_case
add wave -noupdate /tb_apb_slave/tb_pslverr
add wave -noupdate /tb_apb_slave/tb_expected_pslverr
add wave -noupdate /tb_apb_slave/tb_paddr
add wave -noupdate /tb_apb_slave/tb_psel
add wave -noupdate /tb_apb_slave/tb_penable
add wave -noupdate /tb_apb_slave/tb_pwrite
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {339112 ps} 0}
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
WaveRestoreZoom {0 ps} {504320 ps}
