// controller_interface.v
module controller_interface(
    input PCLK,
    inout data_line,
    output wire sigout,
	output reg [2:0] monitor_sig,
    output reg [1:0]LED_test,

    /*** APB3 BUS INTERFACE ***/
    input PRESERN, 				// system reset
    input PSEL, 				// peripheral select
    input PENABLE, 				// distinguishes access phase
    output wire PREADY, 		// peripheral ready signal
    output wire PSLVERR,		// error signal
    input PWRITE,				// distinguishes read and write cycles
    input [31:0] PADDR,			// I/O address
    input wire [31:0] PWDATA,	// data from processor to I/O device (32 bits)
    output reg [31:0] PRDATA	// data to processor from I/O device (32-bits)

);
`define TICKS_PER_MICRO 25 // clock frequecny in MHz = ticks per micro second



///////////////////////////////DECLARATIONS//////////////////////////
//*********STATE MACHINE DECLARATIONS***************//
reg[2:0] state;
reg[2:0] next_state;
reg[31:0] N64_bits_sent; //keeps track of how many N64 bits we've sent
reg[31:0] N64_bits_received; //keeps track of how many N64 bits we've received
reg[31:0] set_high_count; //this is the count that after sending zero, we send a one until global_count reachs
reg[31:0] set_low_count; //this is the count that until global_count reachs, we send a zero
reg[31:0] read_bit_count;
reg[31:0] finish_read_bit_count;
reg N64_bits_sent_incremented;
reg N64_bits_received_incremented;
reg[32:0] controller_data_accumulator; // we update bits in this array in the reading process
reg[32:0] controller_data; // after reading all bits we update all buttons' status

parameter IDLE = 3'b000;
parameter INIT_BIT_SEND = 3'b001;
parameter SEND_N64_BIT = 3'b010;
parameter UPDATE_N64_BIT_COUNT = 3'b011;
parameter INIT_BIT_RECEIVE = 3'b100;
parameter RECEIVE_BIT = 3'b101;
parameter UPDATE_N64_BIT_RECEIVED_COUNT = 3'b110;
parameter WAITE = 3'b111;
//*********END STATE MACHINE DECLARATIONS***************//

reg [31:0] global_count;//global counter based on clock frequency
reg [31:0] temp_global_count;//global counter based on clock frequency


reg [1:0] sync_data_line;
reg request_data; //data to put onto the dataline if sending request packet

// the two registers below are used to sync with the signal received from the N64
reg data_line_went_high;
reg data_line_went_low;

//test signal TEMPORARY
reg temp;
///////////////////////////////END OF DECLARATIONS// ////////////////////////


assign sigout = PRDATA[0];

always @(negedge PCLK) begin 

	monitor_sig [0] <= data_line_went_high;
	monitor_sig [1] <= data_line_went_low;
	monitor_sig [2] <= controller_data_accumulator[N64_bits_received];
end 

//control inout pin
assign data_line = (state == SEND_N64_BIT || state == INIT_BIT_SEND )? request_data : 1'bz;

//tick counter
//micro second counter
always @ (posedge PCLK)
begin 

    global_count <= global_count + 1;

    if(state == IDLE )//|| state == UPDATE_N64_BIT_RECEIVED_COUNT)
    begin
        global_count <= 0; //prevents overflow. also reset count when finished requesting & finished reading
    end


end//end always


//*********REQUEST STATE MACHINE***************//
always@(posedge PCLK)//*
begin
    
    if(~PRESERN)
        next_state = IDLE;

    case(state)
    IDLE:           begin 
                        if(N64_bits_sent == 0 && N64_bits_received == 0) 
                            next_state = INIT_BIT_SEND;
                        else 
                            next_state = IDLE;
                    end

    INIT_BIT_SEND:   begin 
                        if(N64_bits_sent < 9) 
                            next_state = SEND_N64_BIT;
                        else 
                            next_state = RECEIVE_BIT;//TODO INIT_BIT_RECEIVE;
                    end

    SEND_N64_BIT:   begin    
                        if(global_count >= set_high_count) 
                            next_state = UPDATE_N64_BIT_COUNT;
                        else
                            next_state = SEND_N64_BIT;
                    end

    UPDATE_N64_BIT_COUNT: 
                    begin
                         if(N64_bits_sent_incremented) 
                                next_state = INIT_BIT_SEND;
                        else
                            next_state = UPDATE_N64_BIT_COUNT;
                    end

    INIT_BIT_RECEIVE:   begin 
                        if(N64_bits_received >= 33) begin 
                            next_state = WAITE;
						end
                        else begin 
                            next_state = RECEIVE_BIT;
						end
                    end
                    
    RECEIVE_BIT:        begin  
                         if(global_count > read_bit_count)begin //finish_read_bit_count) 
							data_line_went_high = 0;
							data_line_went_low = 0;
                            next_state = UPDATE_N64_BIT_RECEIVED_COUNT;
						end
                        else begin 
							data_line_went_high = 0;
							data_line_went_low = 0;
                            next_state = RECEIVE_BIT;
						end
                    end

    UPDATE_N64_BIT_RECEIVED_COUNT:
                    begin 
                         if(data_line_went_high && data_line_went_low) begin //N64_bits_received_incremented )
							next_state = INIT_BIT_RECEIVE;
						end
						else if (global_count > finish_read_bit_count) begin
							next_state = INIT_BIT_RECEIVE;
						end
                        else begin 
                            next_state = UPDATE_N64_BIT_RECEIVED_COUNT;
							if(sync_data_line[1])
								data_line_went_high = 1;
							if( data_line_went_high && ~sync_data_line[1])
								data_line_went_low = 1;
						end
                    end

    WAITE:           begin 
                        if(global_count < (1000 * `TICKS_PER_MICRO))
                            next_state = WAITE;
                        else 
                            next_state = IDLE;
                    end

    default:        begin     
                        next_state = IDLE;
                    end
    
    endcase
end

always @(posedge PCLK)
begin
    state <= next_state;
    
	sync_data_line[0] <= data_line;
	sync_data_line[1] <= sync_data_line[0];
end


always@(posedge PCLK)
begin

    case(state)
    IDLE:           begin 
                            N64_bits_received = 0;
                            N64_bits_received_incremented = 0;
                            N64_bits_sent_incremented = 0;
                            N64_bits_sent = 0;
                        end

    INIT_BIT_SEND:      begin 

                            temp_global_count = global_count;
                            read_bit_count = temp_global_count + `TICKS_PER_MICRO;
							finish_read_bit_count = temp_global_count + (4 * `TICKS_PER_MICRO);

                            if(N64_bits_sent < 7) // we must send 7 N64 zero bits
                                begin
                                    set_low_count = temp_global_count + (3 * `TICKS_PER_MICRO); //threshold to send zero until
                                    set_high_count = temp_global_count + (4 * `TICKS_PER_MICRO); //threshold to send one after zero until
                                end
                            else 
                                begin
                                    set_low_count = temp_global_count + (1 * `TICKS_PER_MICRO); //threshold to send zero until
                                    set_high_count = temp_global_count + (4 * `TICKS_PER_MICRO); //threshold to send one after zero until
                                end
                           
                        end

    SEND_N64_BIT:       begin            
                            N64_bits_sent_incremented = 0;
                            if (global_count < set_low_count)
                                request_data = 0; //set dataline low
                            else if ( global_count < set_high_count)
                                request_data = 1; //set dataline high
                            else begin
                                    request_data = 0;
                                end
                        end
    UPDATE_N64_BIT_COUNT:   begin
                                if(N64_bits_sent_incremented == 0)
                                begin
                                    N64_bits_sent = N64_bits_sent + 1;
                                    N64_bits_sent_incremented = 1;
                                end
                         end
    INIT_BIT_RECEIVE: begin             temp = 0;
                            temp_global_count = global_count;
                            read_bit_count = temp_global_count + (2 * `TICKS_PER_MICRO); //threshold to wait until to read bit from data line
							finish_read_bit_count = temp_global_count + (4 * `TICKS_PER_MICRO);
                      end
    RECEIVE_BIT: begin 
                    if(global_count == read_bit_count) begin            temp = 1;
                        controller_data_accumulator[N64_bits_received] = sync_data_line[1];
                    end
                    N64_bits_received_incremented = 0;
                    
                 end

    UPDATE_N64_BIT_RECEIVED_COUNT: begin        temp = 0 ;   
                                    if(N64_bits_received_incremented == 0)
                                    begin
                                        N64_bits_received = N64_bits_received + 1;
                                        N64_bits_received_incremented = 1;
                                        
                                    end  
                                   end
    WAITE: begin // to get access to complete data all the time we utilize this stage to allign the valid controller_data with controller_data_accumulator
		if(controller_data_accumulator != controller_data)
			controller_data = controller_data_accumulator;
	end

    default:            begin
                        end
    endcase
end

//*********END REQUEST STATE MACHINE***************//

always@(posedge PCLK)
begin
    LED_test[0] <= ~controller_data[0]; //A button
    LED_test[1] <= ~controller_data[1]; //B button
end

always@(posedge PCLK)
begin
    PRDATA[31:0] <= controller_data[31:0];
end


endmodule