//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Apr 06 09:58:51 2017
// Version: v11.7 SP1 11.7.1.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// N64_controller_iter_4
module N64_controller_iter_4(
    // Inputs
    MSS_RESET_N,
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
input        MSS_RESET_N;
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
wire   [31:0] CoreAPB3_0_APBmslave0_PADDR;
wire          CoreAPB3_0_APBmslave0_PENABLE;
wire   [31:0] CoreAPB3_0_APBmslave0_PRDATA;
wire          CoreAPB3_0_APBmslave0_PREADY;
wire          CoreAPB3_0_APBmslave0_PSELx;
wire          CoreAPB3_0_APBmslave0_PSLVERR;
wire   [31:0] CoreAPB3_0_APBmslave0_PWDATA;
wire          CoreAPB3_0_APBmslave0_PWRITE;
wire          data_line;
wire   [1:0]  LED_test_net_0;
wire   [2:0]  monitor_sig_net_0;
wire          MSS_RESET_N;
wire          N64_controller_iter_4_MSS_0_FAB_CLK;
wire          N64_controller_iter_4_MSS_0_M2F_RESET_N;
wire          N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PENABLE;
wire   [31:0] N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PRDATA;
wire          N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PREADY;
wire          N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSELx;
wire          N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSLVERR;
wire   [31:0] N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWDATA;
wire          N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWRITE;
wire          sigout_net_0;
wire          UART_0_RXD;
wire          UART_0_TXD_1;
wire          sigout_net_1;
wire          UART_0_TXD_1_net_0;
wire   [2:0]  monitor_sig_net_1;
wire   [1:0]  LED_test_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          GND_net;
wire          VCC_net;
wire   [31:0] IADDR_const_net_0;
wire   [31:0] PRDATAS1_const_net_0;
wire   [31:0] PRDATAS2_const_net_0;
wire   [31:0] PRDATAS3_const_net_0;
wire   [31:0] PRDATAS4_const_net_0;
wire   [31:0] PRDATAS5_const_net_0;
wire   [31:0] PRDATAS6_const_net_0;
wire   [31:0] PRDATAS7_const_net_0;
wire   [31:0] PRDATAS8_const_net_0;
wire   [31:0] PRDATAS9_const_net_0;
wire   [31:0] PRDATAS10_const_net_0;
wire   [31:0] PRDATAS11_const_net_0;
wire   [31:0] PRDATAS12_const_net_0;
wire   [31:0] PRDATAS13_const_net_0;
wire   [31:0] PRDATAS14_const_net_0;
wire   [31:0] PRDATAS15_const_net_0;
wire   [31:0] PRDATAS16_const_net_0;
//--------------------------------------------------------------------
// Bus Interface Nets Declarations - Unequal Pin Widths
//--------------------------------------------------------------------
wire   [19:0] N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR;
wire   [31:20]N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_31to20;
wire   [19:0] N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_19to0;
wire   [31:0] N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign GND_net               = 1'b0;
assign VCC_net               = 1'b1;
assign IADDR_const_net_0     = 32'h00000000;
assign PRDATAS1_const_net_0  = 32'h00000000;
assign PRDATAS2_const_net_0  = 32'h00000000;
assign PRDATAS3_const_net_0  = 32'h00000000;
assign PRDATAS4_const_net_0  = 32'h00000000;
assign PRDATAS5_const_net_0  = 32'h00000000;
assign PRDATAS6_const_net_0  = 32'h00000000;
assign PRDATAS7_const_net_0  = 32'h00000000;
assign PRDATAS8_const_net_0  = 32'h00000000;
assign PRDATAS9_const_net_0  = 32'h00000000;
assign PRDATAS10_const_net_0 = 32'h00000000;
assign PRDATAS11_const_net_0 = 32'h00000000;
assign PRDATAS12_const_net_0 = 32'h00000000;
assign PRDATAS13_const_net_0 = 32'h00000000;
assign PRDATAS14_const_net_0 = 32'h00000000;
assign PRDATAS15_const_net_0 = 32'h00000000;
assign PRDATAS16_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign sigout_net_1       = sigout_net_0;
assign sigout             = sigout_net_1;
assign UART_0_TXD_1_net_0 = UART_0_TXD_1;
assign UART_0_TXD         = UART_0_TXD_1_net_0;
assign monitor_sig_net_1  = monitor_sig_net_0;
assign monitor_sig[2:0]   = monitor_sig_net_1;
assign LED_test_net_1     = LED_test_net_0;
assign LED_test[1:0]      = LED_test_net_1;
//--------------------------------------------------------------------
// Bus Interface Nets Assignments - Unequal Pin Widths
//--------------------------------------------------------------------
assign N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_31to20 = 12'h0;
assign N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_19to0 = N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR[19:0];
assign N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0 = { N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_31to20, N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0_19to0 };

//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------controller_interface
controller_interface #( 
        .IDLE                          ( 0 ),
        .INIT_BIT_RECEIVE              ( 4 ),
        .INIT_BIT_SEND                 ( 1 ),
        .RECEIVE_BIT                   ( 5 ),
        .SEND_N64_BIT                  ( 2 ),
        .UPDATE_N64_BIT_COUNT          ( 3 ),
        .UPDATE_N64_BIT_RECEIVED_COUNT ( 6 ),
        .WAITE                         ( 7 ) )
controller_interface_0(
        // Inputs
        .PCLK        ( N64_controller_iter_4_MSS_0_FAB_CLK ),
        .PRESERN     ( N64_controller_iter_4_MSS_0_M2F_RESET_N ),
        .PSEL        ( CoreAPB3_0_APBmslave0_PSELx ),
        .PENABLE     ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE      ( CoreAPB3_0_APBmslave0_PWRITE ),
        .PADDR       ( CoreAPB3_0_APBmslave0_PADDR ),
        .PWDATA      ( CoreAPB3_0_APBmslave0_PWDATA ),
        // Outputs
        .sigout      ( sigout_net_0 ),
        .monitor_sig ( monitor_sig_net_0 ),
        .LED_test    ( LED_test_net_0 ),
        .PREADY      ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERR     ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .PRDATA      ( CoreAPB3_0_APBmslave0_PRDATA ),
        // Inouts
        .data_line   ( data_line ) 
        );

//--------CoreAPB3   -   Actel:DirectCore:CoreAPB3:4.1.100
CoreAPB3 #( 
        .APB_DWIDTH      ( 32 ),
        .APBSLOT0ENABLE  ( 1 ),
        .APBSLOT1ENABLE  ( 0 ),
        .APBSLOT2ENABLE  ( 0 ),
        .APBSLOT3ENABLE  ( 0 ),
        .APBSLOT4ENABLE  ( 0 ),
        .APBSLOT5ENABLE  ( 0 ),
        .APBSLOT6ENABLE  ( 0 ),
        .APBSLOT7ENABLE  ( 0 ),
        .APBSLOT8ENABLE  ( 0 ),
        .APBSLOT9ENABLE  ( 0 ),
        .APBSLOT10ENABLE ( 0 ),
        .APBSLOT11ENABLE ( 0 ),
        .APBSLOT12ENABLE ( 0 ),
        .APBSLOT13ENABLE ( 0 ),
        .APBSLOT14ENABLE ( 0 ),
        .APBSLOT15ENABLE ( 0 ),
        .FAMILY          ( 18 ),
        .IADDR_OPTION    ( 0 ),
        .MADDR_BITS      ( 12 ),
        .SC_0            ( 0 ),
        .SC_1            ( 0 ),
        .SC_2            ( 0 ),
        .SC_3            ( 0 ),
        .SC_4            ( 0 ),
        .SC_5            ( 0 ),
        .SC_6            ( 0 ),
        .SC_7            ( 0 ),
        .SC_8            ( 0 ),
        .SC_9            ( 0 ),
        .SC_10           ( 0 ),
        .SC_11           ( 0 ),
        .SC_12           ( 0 ),
        .SC_13           ( 0 ),
        .SC_14           ( 0 ),
        .SC_15           ( 0 ),
        .UPR_NIBBLE_POSN ( 2 ) )
CoreAPB3_0(
        // Inputs
        .PRESETN    ( GND_net ), // tied to 1'b0 from definition
        .PCLK       ( GND_net ), // tied to 1'b0 from definition
        .PADDR      ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR_0 ),
        .PWRITE     ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWRITE ),
        .PENABLE    ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PENABLE ),
        .PWDATA     ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWDATA ),
        .PSEL       ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSELx ),
        .PRDATAS0   ( CoreAPB3_0_APBmslave0_PRDATA ),
        .PREADYS0   ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERRS0  ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .PRDATAS1   ( PRDATAS1_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS1   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS1  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS2   ( PRDATAS2_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS2   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS2  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS3   ( PRDATAS3_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS3   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS3  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS4   ( PRDATAS4_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS4   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS4  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS5   ( PRDATAS5_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS5   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS5  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS6   ( PRDATAS6_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS6   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS6  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS7   ( PRDATAS7_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS7   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS7  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS8   ( PRDATAS8_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS8   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS8  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS9   ( PRDATAS9_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS9   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS9  ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS10  ( PRDATAS10_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS10  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS10 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS11  ( PRDATAS11_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS11  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS11 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS12  ( PRDATAS12_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS12  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS12 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS13  ( PRDATAS13_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS13  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS13 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS14  ( PRDATAS14_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS14  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS14 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS15  ( PRDATAS15_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS15  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS15 ( GND_net ), // tied to 1'b0 from definition
        .PRDATAS16  ( PRDATAS16_const_net_0 ), // tied to 32'h00000000 from definition
        .PREADYS16  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS16 ( GND_net ), // tied to 1'b0 from definition
        .IADDR      ( IADDR_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .PRDATA     ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PRDATA ),
        .PREADY     ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PREADY ),
        .PSLVERR    ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSLVERR ),
        .PADDRS     ( CoreAPB3_0_APBmslave0_PADDR ),
        .PWRITES    ( CoreAPB3_0_APBmslave0_PWRITE ),
        .PENABLES   ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWDATAS    ( CoreAPB3_0_APBmslave0_PWDATA ),
        .PSELS0     ( CoreAPB3_0_APBmslave0_PSELx ),
        .PSELS1     (  ),
        .PSELS2     (  ),
        .PSELS3     (  ),
        .PSELS4     (  ),
        .PSELS5     (  ),
        .PSELS6     (  ),
        .PSELS7     (  ),
        .PSELS8     (  ),
        .PSELS9     (  ),
        .PSELS10    (  ),
        .PSELS11    (  ),
        .PSELS12    (  ),
        .PSELS13    (  ),
        .PSELS14    (  ),
        .PSELS15    (  ),
        .PSELS16    (  ) 
        );

//--------N64_controller_iter_4_MSS
N64_controller_iter_4_MSS N64_controller_iter_4_MSS_0(
        // Inputs
        .UART_0_RXD  ( UART_0_RXD ),
        .MSSPRDATA   ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PRDATA ),
        .MSSPREADY   ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PREADY ),
        .MSSPSLVERR  ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSLVERR ),
        .MSS_RESET_N ( MSS_RESET_N ),
        // Outputs
        .FAB_CLK     ( N64_controller_iter_4_MSS_0_FAB_CLK ),
        .UART_0_TXD  ( UART_0_TXD_1 ),
        .M2F_RESET_N ( N64_controller_iter_4_MSS_0_M2F_RESET_N ),
        .MSSPADDR    ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PADDR ),
        .MSSPSEL     ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PSELx ),
        .MSSPENABLE  ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PENABLE ),
        .MSSPWRITE   ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWRITE ),
        .MSSPWDATA   ( N64_controller_iter_4_MSS_0_MSS_MASTER_APB_PWDATA ) 
        );


endmodule
