onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_fir_filter/tb_clk
add wave -noupdate /tb_fir_filter/tb_std_test_case
add wave -noupdate /tb_fir_filter/DUT/CONT/state
add wave -noupdate -radix unsigned /tb_fir_filter/tb_modwait
add wave -noupdate -radix unsigned /tb_fir_filter/tb_err
add wave -noupdate -radix unsigned /tb_fir_filter/tb_one_k_samples
add wave -noupdate -radix decimal -childformat {{{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[9]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[8]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[7]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[6]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[5]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[4]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[3]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[2]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[1]} -radix decimal} {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[0]} -radix decimal}} -subitemconfig {{/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[9]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[8]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[7]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[6]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[5]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[4]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[3]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[2]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[1]} {-height 16 -radix decimal} {/tb_fir_filter/DUT/CNT1000/CNT1000/count_out[0]} {-height 16 -radix decimal}} /tb_fir_filter/DUT/CNT1000/CNT1000/count_out
add wave -noupdate -radix decimal /tb_fir_filter/tb_fir_out
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {953665423 ps} 0}
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
WaveRestoreZoom {0 ps} {2042256 ps}
