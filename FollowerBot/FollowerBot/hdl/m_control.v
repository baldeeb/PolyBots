// motor_control.v
module m_control(
    /*** APB3 BUS INTERFACE ***/
    input PCLK, // clock
    input PRESERN, // system reset
    input PSEL, // peripheral select
    input PENABLE, // distinguishes access phase
    output wire PREADY, // peripheral ready signal
    output wire PSLVERR, // error signal
    input PWRITE, // distinguishes read and write cycles
    input [31:0] PADDR, // I/O address
    input wire [31:0] PWDATA, // data from processor to I/O device (32 bits)
    output reg [31:0] PRDATA, // data to processor from I/O device (32-bits)
    output reg pwmLeft,
    output reg pwmRight,
    output reg [3:0]inputsAB,
    input [1:0]encoder
);

    `define period 500000
    `define second 25000000

    reg [18:0]pulseWidthLeft;
    reg [18:0]pulseWidthRight;
    reg [18:0]count;
    reg [24:0]counter;
        
    assign PSLVERR = 0;
    assign PREADY = 1;
    wire PW_write;
    assign PW_write = PSEL & PENABLE & PWRITE;
    wire PW_read;
    assign PW_read = PSEL & ~PWRITE;

    always @(posedge PCLK)
    begin
        if(!PRESERN)
        begin
            pulseWidthLeft[18:0] <= 18'h00000;
            pulseWidthRight[18:0] <= 18'h00000;
        end
        else if(PW_write)
        begin
            if(PADDR[7:0] == 8'h04)
                inputsAB[3:0] <= PWDATA[3:0];
            else if(PADDR[7:0] == 8'h08)
                pulseWidthLeft[18:0] <= PWDATA[18:0];
            else if(PADDR[7:0] == 8'h0c)
                pulseWidthRight[18:0] <= PWDATA[18:0];
        end
        else if(PW_read)
        begin
            if(PADDR[7:0] == 8'h08)
            begin
                PRDATA[31:19] <= 13'h0000;
                PRDATA[18:0] <= pulseWidthLeft[18:0];
            end
            else if(PADDR[7:0] == 8'h0c)
            begin
                PRDATA[31:19] <= 13'h0000;
                PRDATA[18:0] <= pulseWidthRight[18:0];
            end
            else if(PADDR[7:0] == 8'h10)
            begin
                PRDATA[31:2] <= 30'h00000000;
                PRDATA[1:0] <= encoder[1:0];
            end
            else if(PADDR[7:0] == 8'h14)
            begin
                PRDATA[31:25] <= 7'h00;
                PRDATA[24:0] <= counter[24:0];
            end
        end

    end

    always @(posedge PCLK)
    begin
        if (count == `period)
            count <= 0;
        else
            count <= count + 1;

        if (counter == `second)
            counter <= 0;
        else
            counter <= counter + 1;
        
        if (count < pulseWidthLeft)
            pwmLeft <= 1;
        else
            pwmLeft <= 0;

        if (count < pulseWidthRight)
            pwmRight <= 1;
        else
            pwmRight <= 0;
    end
endmodule
