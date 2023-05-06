onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_ahb_lite_fir_filter/tb_clk
add wave -noupdate /tb_ahb_lite_fir_filter/tb_n_rst
add wave -noupdate -radix hexadecimal -childformat {{{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[15]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[14]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[13]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[12]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[11]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[10]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[9]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[8]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[7]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[6]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[5]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[4]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[3]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[2]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[1]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[0]} -radix hexadecimal}} -subitemconfig {{/tb_ahb_lite_fir_filter/DUT/fir_coefficient[15]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[14]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[13]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[12]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[11]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[10]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[9]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[8]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[7]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[6]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[5]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[4]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[3]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[2]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[1]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/fir_coefficient[0]} {-height 16 -radix hexadecimal}} /tb_ahb_lite_fir_filter/DUT/fir_coefficient
add wave -noupdate -radix unsigned /tb_ahb_lite_fir_filter/DUT/AHBLITE/htrans
add wave -noupdate -radix unsigned /tb_ahb_lite_fir_filter/DUT/haddr
add wave -noupdate -radix hexadecimal /tb_ahb_lite_fir_filter/tb_hwdata
add wave -noupdate -radix hexadecimal -childformat {{{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[15]} -radix binary} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[14]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[13]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[12]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[11]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[10]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[9]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[8]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[7]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[6]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[5]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[4]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[3]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[2]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[1]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[0]} -radix hexadecimal}} -subitemconfig {{/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[15]} {-height 16 -radix binary} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[14]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[13]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[12]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[11]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[10]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[9]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[8]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[7]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[6]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[5]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[4]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[3]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[2]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[1]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/AHBLITE/F0[0]} {-height 16 -radix hexadecimal}} /tb_ahb_lite_fir_filter/DUT/AHBLITE/F0
add wave -noupdate -radix hexadecimal /tb_ahb_lite_fir_filter/DUT/AHBLITE/F1
add wave -noupdate -radix hexadecimal /tb_ahb_lite_fir_filter/DUT/AHBLITE/F2
add wave -noupdate -radix hexadecimal /tb_ahb_lite_fir_filter/DUT/AHBLITE/F3
add wave -noupdate /tb_ahb_lite_fir_filter/DUT/load_coeff
add wave -noupdate /tb_ahb_lite_fir_filter/DUT/modwait
add wave -noupdate /tb_ahb_lite_fir_filter/DUT/new_coefficient_set
add wave -noupdate /tb_ahb_lite_fir_filter/DUT/FIR/CONT/state
add wave -noupdate -childformat {{{/tb_ahb_lite_fir_filter/DUT/FIR/DPATH/RF/regs_matrix[8]} -radix hexadecimal} {{/tb_ahb_lite_fir_filter/DUT/FIR/DPATH/RF/regs_matrix[7]} -radix hexadecimal}} -subitemconfig {{/tb_ahb_lite_fir_filter/DUT/FIR/DPATH/RF/regs_matrix[8]} {-height 16 -radix hexadecimal} {/tb_ahb_lite_fir_filter/DUT/FIR/DPATH/RF/regs_matrix[7]} {-height 16 -radix hexadecimal}} /tb_ahb_lite_fir_filter/DUT/FIR/DPATH/RF/regs_matrix
add wave -noupdate -radix decimal /tb_ahb_lite_fir_filter/DUT/FIR/fir_out
add wave -noupdate -radix decimal /tb_ahb_lite_fir_filter/tb_hrdata
add wave -noupdate /tb_ahb_lite_fir_filter/DUT/FIR/sample_data
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {1413468 ps} 0}
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
WaveRestoreZoom {0 ps} {1491 ns}
