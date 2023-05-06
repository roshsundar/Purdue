#######################################################
#                                                     
#  Innovus Command Logging File                     
#  Created on Tue Apr  4 17:27:59 2023                
#                                                     
#######################################################

#@(#)CDS: Innovus v16.12-s051_1 (64bit) 08/17/2016 12:18 (Linux 2.6.18-194.el5)
#@(#)CDS: NanoRoute 16.12-s051_1 NR160816-1350/16_12-UB (database version 2.30, 347.6.1) {superthreading v1.30}
#@(#)CDS: AAE 16.12-s026 (64bit) 08/17/2016 (Linux 2.6.18-194.el5)
#@(#)CDS: CTE 16.12-s023_1 () Aug 12 2016 01:35:46 ( )
#@(#)CDS: SYNTECH 16.12-s009_1 () Aug 11 2016 01:33:09 ( )
#@(#)CDS: CPE v16.12-s054
#@(#)CDS: IQRC/TQRC 15.2.4-s467 (64bit) Wed Jul 20 17:12:38 PDT 2016 (Linux 2.6.18-194.el5)

set_global _enable_mmmc_by_default_flow      $CTE::mmmc_default
suppressMessage ENCEXT-2799
getDrawView
loadWorkspace -name Physical
win
set_global _enable_mmmc_by_default_flow      $CTE::mmmc_default
suppressMessage ENCEXT-2799
getDrawView
loadWorkspace -name Physical
win
set ::TimeLib::tsgMarkCellLatchConstructFlag 1
set conf_qxconf_file NULL
set conf_qxlib_file NULL
set defHierChar /
set delaycal_input_transition_delay 0.1ps
set distributed_client_message_echo 1
set distributed_mmmc_disable_reports_auto_redirection 0
set floorplan_default_site core
set fpIsMaxIoHeight 0
set init_gnd_net gnd
set init_io_file innovus.io
set init_lef_file {/package/eda/cells/OSU/v2.7/cadence/lib/ami05/lib/osu05_stdcells.lef /package/eda/cells/OSU/v2.7/cadence/lib/ami05/lib/osu05_stdcells.stacks.lef}
set init_mmmc_file osu05_MMMC.view
set init_oa_search_lib {}
set init_pwr_net vdd
set init_verilog mapped/layout_lab_design.v
set latch_time_borrow_mode max_borrow
set pegDefaultResScaleFactor 1
set pegDetailResScaleFactor 1
set report_inactive_arcs_format {from to when arc_type sense reason}
set timing_library_ccs_noise_vin_clip_points {}
set timing_library_ccs_noise_vout_clip_points {}
set timing_library_load_pin_cap_indices {}
set timing_library_write_library_to_directory {}
set tso_post_client_restore_command {update_timing ; write_eco_opt_db ;}
init_design
floorPlan -r 1.0 0.6 50 50 50 50
unfixAllIos
legalizePin
addRing -spacing_bottom 9.9 -width_left 9.9 -width_bottom 9.9 -width_top 9.9 -spacing_top 9.9 -layer_bottom metal1 -width_right 9.9 -around default_power_domain -center 1 -layer_top metal1 -spacing_right 9.9 -spacing_left 9.9 -layer_right metal2 -layer_left metal2 -offset 9.9 -nets { gnd vdd }
setPlaceMode -congEffort medium
placeDesign -inPlaceOpt
checkPlace
pan -196.747 -61.692
sroute
zoomBox -233.508 1160.081 -273.524 1048.369
pan -321.939 -83.466
trialRoute
timeDesign -preCTS
pan 114.576 -8.958
pan 102.493 29.581
pan -20.883 33.040
pan -0.177 54.184
pan 1.667 51.247
pan -246.132 4.249
pan -199.385 2.833
pan -182.740 10.270
pan 135.461 6.020
pan 65.340 1.947
pan 95.797 13.280
pan 11.854 -4.785
pan -298.545 4.790
pan 47.698 -11.237
pan 58.934 -6.679
pan 68.914 -2.043
pan 52.963 0.000
pan -106.044 15.879
pan -113.222 11.094
pan -77.983 15.227
pan 38.829 -14.792
pan 15.227 -27.517
pan 24.254 1.305
pan 30.236 0.000
pan 89.839 2.611
pan 100.279 -1.196
pan 52.424 0.000
pan 140.957 16.641
pan 120.509 2.501
pan 143.133 -1.197
pan 42.961 -17.511
pan -19.229 11.257
setOptMode -yieldEffort none
setOptMode -highEffort
setOptMode -maxDensity 0.95
setOptMode -drcMargin 0.0
setOptMode -holdTargetSlack 0.0 -setupTargetSlack 0.0
setOptMode -noSimplifyNetlist
optDesign -preCTS -drv
trialRoute
timeDesign -postCTS
setExtractRCMode -assumeMetFill
extractRC -outfile encounter.cap
setOptMode -yieldEffort none
setOptMode -highEffort
setOptMode -maxDensity 0.95
setOptMode -drcMargin 0.0
setOptMode -holdTargetSlack 0.0 -setupTargetSlack 0.0
setOptMode -noSimplifyNetlist
optDesign -postCTS -hold
optDesign -postCTS -drv
all_hold_analysis_views
all_setup_analysis_views
getPlaceMode -doneQuickCTS -quiet
addFiller -cell FILL
globalNetConnect vdd -type tiehi
globalNetConnect vdd -type pgpin -pin vdd -all -override
globalNetConnect gnd -type tielo
globalNetConnect gnd -type pgpin -pin gnd -all -override
sroute
globalDetailRoute
pan -221.577 -137.036
pan -48.693 -158.780
pan -164.338 -46.205
pan -12.682 -124.937
pan -13.151 -130.573
pan -10.803 -138.088
pan 134.330 60.590
pan 33.481 -47.652
setExtractRCMode -engine postRoute -effortLevel low -reduce 0.0
extractRC
setAnalysisMode -analysisType onChipVariation
setOptMode -yieldEffort none
setOptMode -effort high
setOptMode -maxDensity 0.95
setOptMode -drcMargin 0.0
setOptMode -holdTargetSlack 0.0 -setupTargetSlack 0.0
setOptMode -simplifyNetlist false
setOptMode -usefulSkew false
optDesign -postRoute -incr
addFiller -cell FILL -prefix FIL -fillBoundary
ecoRoute
pan -347.106 106.152
pan 74.682 294.970
pan 4.697 -118.363
pan -9.864 -163.455
pan 13.152 -135.273
pan 33.818 69.045
pan 121.490 -66.175
pan 30.241 -11.653
pan 14.360 -16.969
redirect -quiet {set honorDomain [getAnalysisMode -honorClockDomains]} > /dev/null
timeDesign -postRoute -pathReports -drvReports -slackReports -numPaths 50 -prefix layout_lab_design_postRoute -outDir timingReports
get_time_unit
report_timing -machine_readable -max_points 10000 -max_slack 0.75 -path_exceptions all > top.mtarpt
load_timing_debug_report -name default_report top.mtarpt
uiKit::addWidget .dodo -type main
uiKit::addWidget gtd@frameOnly_detail -type main
uiKit::addWidget sgnviewer_tdg_frame -type main -closecmd {::sgn::quitApply sgnviewer_tdg_frame}
uiKit::addWidget sgnviewer_tdg_frame.ib -type statusbar -in sgnviewer_tdg_frame
uiKit::addWidget sgnviewer_tdg_frame.msg -type message -variable ::csv::infoMsg(sgnviewer_tdg_frame) -stretch 1
pan 206.286 -61.741
pan 183.493 -83.668
pan -397.792 116.098
pan -440.990 -148.812
pan -34.199 248.395
pan -1.800 56.698
pan 15.299 211.496
pan 192.596 -64.799
pan -15.299 -335.694
pan 143.098 213.296
pan -117.003 -19.966
pan -59.900 -155.739
pan 25.557 -165.722
pan 23.720 -142.022
pan -175.704 6.788
pan -451.640 15.175
pan -5.191 41.530
pan -1.997 182.893
pan 142.811 -15.061
pan 68.275 -50.760
pan 252.361 -101.533
pan 221.214 -0.981
pan 56.407 41.937
pan 44.145 159.412
pan -17.167 99.816
pan 154.469 -6.879
pan -120.843 -90.972
uiKit::addWidget .dodo -type main
uiKit::addWidget gtd@frameOnly_detail -type main
uiKit::addWidget sgnviewer_tdg_frame -type main -closecmd {::sgn::quitApply sgnviewer_tdg_frame}
uiKit::addWidget sgnviewer_tdg_frame.ib -type statusbar -in sgnviewer_tdg_frame
uiKit::addWidget sgnviewer_tdg_frame.msg -type message -variable ::csv::infoMsg(sgnviewer_tdg_frame) -stretch 1
pan -34.826 -165.299
pan -103.838 115.636
pan 1.668 5.421
pan -21.805 127.511
pan -513.979 23.084
pan 115.524 108.338
pan -80.637 182.083
pan 27.313 -132.010
deselectAll
