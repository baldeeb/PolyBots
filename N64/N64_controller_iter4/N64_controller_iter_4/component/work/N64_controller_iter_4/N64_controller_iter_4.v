//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Tue Apr 04 16:48:29 2017
// Version: v11.7 SP1 11.7.1.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// N64_controller_iter_4
module N64_controller_iter_4(
    // Inputs
    UART_0_RXD,
    // Outputs
    LED_test,
    UART_0_TXD,
    monitor_sig,
    sigout,
    // Inouts
    data_line
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input        UART_0_RXD;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output [1:0] LED_test;
output       UART_0_TXD;
output [2:0] monitor_sig;
output       sigout;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout        data_line;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire         data_line;
wire   [1:0] LED_test_net_0;
wire   [2:0] monitor_sig_net_0;
wire         N64_controller_iter_4_MSS_0_FAB_CLK;
wire         sigout_net_0;
wire         UART_0_RXD;
wire         UART_0_TXD_0;
wire         sigout_net_1;
wire   [2:0] monitor_sig_net_1;
wire   [1:0] LED_test_net_1;
wire         UART_0_TXD_0_net_0;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign sigout_net_1       = sigout_net_0;
assign sigout             = sigout_net_1;
assign monitor_sig_net_1  = monitor_sig_net_0;
assign monitor_sig[2:0]   = monitor_sig_net_1;
assign LED_test_net_1     = LED_test_net_0;
assign LED_test[1:0]      = LED_test_net_1;
assign UART_0_TXD_0_net_0 = UART_0_TXD_0;
assign UART_0_TXD         = UART_0_TXD_0_net_0;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------controller_interface
controller_interface controller_interface_0(
        // Inputs
        .PCLK        ( N64_controller_iter_4_MSS_0_FAB_CLK ),
        // Outputs
        .sigout      ( sigout_net_0 ),
        .monitor_sig ( monitor_sig_net_0 ),
        .LED_test    ( LED_test_net_0 ),
        // Inouts
        .data_line   ( data_line ) 
        );

//--------N64_controller_iter_4_MSS
N64_controller_iter_4_MSS N64_controller_iter_4_MSS_0(
        // Inputs
        .UART_0_RXD ( UART_0_RXD ),
        // Outputs
        .FAB_CLK    ( N64_controller_iter_4_MSS_0_FAB_CLK ),
        .UART_0_TXD ( UART_0_TXD_0 ) 
        );


endmodule
