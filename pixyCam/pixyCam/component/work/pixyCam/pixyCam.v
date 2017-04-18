//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Apr 13 00:24:57 2017
// Version: v11.7 SP1 11.7.1.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// pixyCam
module pixyCam(
    // Inputs
    MSS_RESET_N,
    SPI_1_DI,
    UART_0_RXD,
    UART_1_RXD,
    // Outputs
    SPI_1_DO,
    UART_0_TXD,
    UART_1_TXD,
    // Inouts
    I2C_1_SCL,
    I2C_1_SDA,
    SPI_1_CLK,
    SPI_1_SS
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  MSS_RESET_N;
input  SPI_1_DI;
input  UART_0_RXD;
input  UART_1_RXD;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output SPI_1_DO;
output UART_0_TXD;
output UART_1_TXD;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  I2C_1_SCL;
inout  I2C_1_SDA;
inout  SPI_1_CLK;
inout  SPI_1_SS;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   I2C_1_SCL;
wire   I2C_1_SDA;
wire   MSS_RESET_N;
wire   SPI_1_CLK;
wire   SPI_1_DI;
wire   SPI_1_DO_0;
wire   SPI_1_SS;
wire   UART_0_RXD;
wire   UART_0_TXD_net_0;
wire   UART_1_RXD;
wire   UART_1_TXD_0;
wire   UART_0_TXD_net_1;
wire   SPI_1_DO_0_net_0;
wire   UART_1_TXD_0_net_0;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign UART_0_TXD_net_1   = UART_0_TXD_net_0;
assign UART_0_TXD         = UART_0_TXD_net_1;
assign SPI_1_DO_0_net_0   = SPI_1_DO_0;
assign SPI_1_DO           = SPI_1_DO_0_net_0;
assign UART_1_TXD_0_net_0 = UART_1_TXD_0;
assign UART_1_TXD         = UART_1_TXD_0_net_0;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------pixyCam_MSS
pixyCam_MSS pixyCam_MSS_0(
        // Inputs
        .MSS_RESET_N ( MSS_RESET_N ),
        .UART_0_RXD  ( UART_0_RXD ),
        .SPI_1_DI    ( SPI_1_DI ),
        .UART_1_RXD  ( UART_1_RXD ),
        // Outputs
        .UART_0_TXD  ( UART_0_TXD_net_0 ),
        .SPI_1_DO    ( SPI_1_DO_0 ),
        .UART_1_TXD  ( UART_1_TXD_0 ),
        // Inouts
        .I2C_1_SCL   ( I2C_1_SCL ),
        .I2C_1_SDA   ( I2C_1_SDA ),
        .SPI_1_CLK   ( SPI_1_CLK ),
        .SPI_1_SS    ( SPI_1_SS ) 
        );


endmodule
