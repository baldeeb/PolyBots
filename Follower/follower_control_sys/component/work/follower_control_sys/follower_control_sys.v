//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Apr 06 16:14:16 2017
// Version: v11.7 SP1 11.7.1.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// follower_control_sys
module follower_control_sys(
    // Inputs
    MSS_RESET_N,
    // Outputs
    trig
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  MSS_RESET_N;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output trig;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   follower_control_sys_MSS_0_FAB_CLK;
wire   MSS_RESET_N;
wire   trig_net_0;
wire   trig_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign trig_net_1 = trig_net_0;
assign trig       = trig_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------follower_control
follower_control follower_control_0(
        // Inputs
        .PCLK ( follower_control_sys_MSS_0_FAB_CLK ),
        // Outputs
        .trig ( trig_net_0 ) 
        );

//--------follower_control_sys_MSS
follower_control_sys_MSS follower_control_sys_MSS_0(
        // Inputs
        .MSS_RESET_N ( MSS_RESET_N ),
        // Outputs
        .FAB_CLK     ( follower_control_sys_MSS_0_FAB_CLK ) 
        );


endmodule
