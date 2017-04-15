// spi_pin.v
module spi_pin(

/*** APB3 BUS INTERFACE ***/
input PCLK, 				// clock
input PRESERN, 				// system reset
input PSEL, 				// peripheral select
input PENABLE, 				// distinguishes access phase
output wire PREADY, 		// peripheral ready signal
output wire PSLVERR,		// error signal
input PWRITE,				// distinguishes read and write cycles
input [31:0] PADDR,			// I/O address
input wire [31:0] PWDATA,	// data from processor to I/O device (32 bits)
output reg [31:0] PRDATA,	// data to processor from I/O device (32-bits)

/*** I/O PORTS DECLARATION ***/	
output reg CD			// port to CD pin
); 

assign PSLVERR = 0;
assign PREADY = 1;

wire CD_write = PENABLE & (PADDR[2] == 1) & PWRITE ;   //enable pin write at offset #4


//////////////////////////////////
// end of APB3 interface header //
//////////////////////////////////


always @(posedge PCLK) 		// register control for APB3 writes
begin
	if(!PRESERN)
		CD <= 1;  // LED should start turned "off"
												// recall it is active low. 
	else if(CD_write)
		CD <= PWDATA[0];
end



endmodule 