module follower_control
(	input PCLK,
	//input echo,
	output reg trig
);
	
	`define TICKS_PER_MICRO 100
	`define COUNT_PER_TRIG (10 * `TICKS_PER_MICRO)
	`define TRIG_END	(60000 * `TICKS_PER_MICRO)
	
	reg [31:0] count;
	reg reset;
	
	always @ (posedge PCLK) begin
		count <= count + 1;
		
		if (reset) begin 
			count <= 0;
		end
	end


	always @ *  begin
		if(count >= `COUNT_PER_TRIG)
			trig = 0;
		else 
			trig = 1;
			
		if (count >= `TRIG_END)
			reset = 1;
		else 
			reset = 0;
	end
	
	
endmodule 