open_project -project {N:\eecs373\PolyBots\TouchScreen\touch_screen\designer\impl1\touch_screen_fp\touch_screen.pro}
set_programming_file -no_file
set_device_type -type {A2F200M3F}
set_device_package -package {484 FBGA}
update_programming_file \
    -feature {prog_fpga:on} \
    -fdb_source {fdb} \
    -fdb_file {N:\eecs373\PolyBots\TouchScreen\touch_screen\designer\impl1\touch_screen.fdb} \
    -feature {prog_from:off} \
    -feature {prog_nvm:on} \
    -efm_content {location:0;source:efc} \
    -efm_block {location:0;config_file:{N:\eecs373\PolyBots\TouchScreen\touch_screen\component\work\touch_screen_MSS\MSS_ENVM_0\MSS_ENVM_0.efc}} \
    -pdb_file {N:\eecs373\PolyBots\TouchScreen\touch_screen\designer\impl1\touch_screen_fp\touch_screen.pdb}
set_programming_action -action {PROGRAM}
run_selected_actions
save_project
close_project
