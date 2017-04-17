/*
 * pixy.c
 *
 *  Created on: Apr 14, 2017
 *      Author: baldeeb
 */
#include "pixy.h"

/* *
 * removes the first uint8_t from the I2C recieve buffer.
 * sometimes the camera sends a zero as a first nibble
 * */
void shift_recieve_union(){
	int i ;
	for(i = 0; i < sizeof(receive_buf)-1; i ++){
		receive_buf.u8[i] = receive_buf.u8[i+1];
	}
}

/* *
 * for testing
 * print pixy data
 * */
void pixy_print(union pixy_data_union *p){
	printf("\n\r\n\r");
	printf("id: %" PRIu16"\n\r", p[0].o.id);
	printf("x: %" PRIu16"\n\r", p[0].o.x);
	printf("y: %" PRIu16"\n\r", p[0].o.y);
	printf("width: %" PRIu16"\n\r", p[0].o.width);
	printf("height: %" PRIu16"\n\r", p[0].o.height);
}


/* *
 * used to properly assign the data read into the i2c buffer to
 * the globally accessible pixy-data data structure
 * */
void pixy_read_multiple( void ){
	int obj_index, buff_index;
	int i;


	//check if the start bits match expected
	for(i=0; i < PIXY_RECIEVE_BUFF_SIZE / 2; i++){
		if (receive_buf.u16[i] != 0){
			break;
		}
	}

	if(receive_buf.u8[0] == 0){	shift_recieve_union(); }

	if((receive_buf.u16[0] != PIXY_START_WORD || receive_buf.u16[1] != PIXY_START_WORD) && i < PIXY_RECIEVE_BUFF_SIZE / 2){
		//printf("Bad start bits in buffer...\n\r");
		//bad data read from successful read
		return;
	}

	for (obj_index = 0; obj_index < PIXY_OBJECT_COUNT; obj_index++){
		for(buff_index = 0 ; buff_index < PIXY_UNION_U16_SIZE ; buff_index++){
			pixy_data[obj_index].u16[buff_index] = receive_buf.u16[(obj_index*PIXY_UNION_U16_SIZE) + buff_index + 1];
		}
		printf("id: %x\n\r",pixy_data[obj_index].o.id );
	}

	update_pixy_data_flag = 0;
}


/* *
 * update the global union holding the pixy data
 * */
void process_pixy_i2c( void ){
	switch(MSS_I2C_get_status(&g_mss_i2c1)){
		case MSS_I2C_SUCCESS:
			if (update_pixy_data_flag){
				pixy_read_multiple();
			}
			break;
		case MSS_I2C_IN_PROGRESS:
			break;
		case MSS_I2C_FAILED:
		case MSS_I2C_TIMED_OUT:
		default:
			printf("i2c transmission issues %x\n\r", MSS_I2C_get_status(&g_mss_i2c1));
	}//switch
}

/* *
 * The desired follower bot's relative x-coordinate
 * */
void init_ideal_pixy_dots( void ){
	pixy_ideal_green.o.sync = 0;
	pixy_ideal_green.o.crc = 0;

	pixy_ideal_green.o.id = 2;

	pixy_ideal_green.o.x = 200;
	pixy_ideal_green.o.y = 67;

	pixy_ideal_green.o.width = 25;
	pixy_ideal_green.o.height = 24;
}


/* *
 * returns the magnitude and direction of the follower
 * bot's x-coordinate offset
 * */
int pixy_x_err( unsigned int *mag, unsigned int *dir){
	int obj_index;

	//look for desired object
	for (obj_index = 0; obj_index < PIXY_OBJECT_COUNT; obj_index++){
		if (pixy_data[obj_index].o.id == 2){
			break;
		}
	}
//	printf("obj_index: %x\n\r",obj_index);
	//return if no object was found
	if(obj_index == PIXY_OBJECT_COUNT){
		*mag = 0;
		*dir = 0;
		return 1;
	}

	int err = pixy_ideal_green.o.x - pixy_data[obj_index].o.x;

	if(err < -5){
		*mag = -err;
		*dir = 2;
	}
	else if (err > 5){
		*mag = err;
		*dir = 1;
	}
	else{
		*dir = 0;
		*mag = 0;
	}
	return 1;
}

/* *
 * setup a continuous hardware timer with interrupt that reads
 * */
void start_hardware_cont_timer( void ){
	MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);
	MSS_TIM1_load_background(PIXY_READ_PERIOD);
	MSS_TIM1_start();
	MSS_TIM1_enable_irq();
}

/* *
 * hardware timer down counting at 100MHz
 * hardware timer down counting
 * */
void Timer1_IRQHandler( void ){
	MSS_I2C_read(&g_mss_i2c1, PIXY_I2C_DEFAULT_ADDR, receive_buf.u8, PIXY_RECIEVE_BUFF_SIZE, MSS_I2C_RELEASE_BUS);
	MSS_TIM1_clear_irq();
	update_pixy_data_flag = 1;
}

