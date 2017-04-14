open_project -project {N:\eecs373\PolyBots\N64\N64_controller_iter4\N64_controller_iter_4\designer\impl1\N64_controller_iter_4_fp\N64_controller_iter_4.pro}
set_programming_file -no_file
set_device_type -type {A2F200M3F}
set_device_package -package {484 FBGA}
update_programming_file \
    -feature {prog_fpga:on} \
    -fdb_source {fdb} \
    -fdb_file {N:\eecs373\PolyBots\N64\N64_controller_iter4\N64_controller_iter_4\designer\impl1\N64_controller_iter_4.fdb} \
    -feature {prog_from:off} \
    -feature {prog_nvm:on} \
    -efm_content {location:0;source:efc} \
    -efm_block {location:0;config_file:{N:\eecs373\PolyBots\N64\N64_controller_iter4\N64_controller_iter_4\component\work\N64_controller_iter_4_MSS\MSS_ENVM_0\MSS_ENVM_0.efc}} \
    -pdb_file {N:\eecs373\PolyBots\N64\N64_controller_iter4\N64_controller_iter_4\designer\impl1\N64_controller_iter_4_fp\N64_controller_iter_4.pdb}
set_programming_action -action {PROGRAM}
run_selected_actions
save_project
close_project
