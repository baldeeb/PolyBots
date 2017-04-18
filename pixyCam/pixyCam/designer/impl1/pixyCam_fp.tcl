new_project \
    -name {pixyCam} \
    -location {N:\eecs373\project\pixyCam\pixyCam\designer\impl1\pixyCam_fp} \
    -mode {single}
set_device_type -type {A2F200M3F}
set_device_package -package {484 FBGA}
update_programming_file \
    -feature {prog_fpga:on} \
    -fdb_source {fdb} \
    -fdb_file {N:\eecs373\project\pixyCam\pixyCam\designer\impl1\pixyCam.fdb} \
    -feature {prog_from:off} \
    -feature {prog_nvm:on} \
    -efm_content {location:0;source:efc} \
    -efm_block {location:0;config_file:{N:\eecs373\project\pixyCam\pixyCam\component\work\pixyCam_MSS\MSS_ENVM_0\MSS_ENVM_0.efc}} \
    -pdb_file {N:\eecs373\project\pixyCam\pixyCam\designer\impl1\pixyCam_fp\pixyCam.pdb}
set_programming_action -action {PROGRAM}
run_selected_actions
save_project
close_project
