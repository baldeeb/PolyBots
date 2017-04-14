#include <stdio.h>
#include <inttypes.h>
#include "drivers/mss_i2c/mss_i2c.h"
#include "mss_timer.h"

#define PIXY_START_WORD             	0xaa55
#define PIXY_START_WORD_CC          	0xaa56
#define PIXY_START_WORDX            	0x55aa
#define PIXY_I2C_DEFAULT_ADDR           0x54

#define PIXY_OBJECT_COUNT 3
#define PIXY_BUFFER_SIZE 14
#define PIXY_RECIEVE_BUFF_SIZE (PIXY_BUFFER_SIZE * PIXY_OBJECT_COUNT)+16

#define PIXY_READ_PERIOD 20000000

union pixy_data_union{
	uint8_t u8[PIXY_BUFFER_SIZE];
	struct{
		uint16_t sync;
		uint16_t crc;
		uint16_t id;
		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;
	}u16;
};

// used to invert endienness
union data_buffer_u{
	uint8_t u8[PIXY_RECIEVE_BUFF_SIZE];
	uint16_t u16[PIXY_RECIEVE_BUFF_SIZE/2];
};



static union data_buffer_u receive_buf;


/* *
 * This function takes in the data from i2c
 * it switches the endienness of bytes and
 * accumulates then in an easy to read union
 * */
int process_pixy_obj(uint8_t *buff, union pixy_data_union * p_buff){
	int i;

	//flip byte endienness
	for (i = 0; i < PIXY_BUFFER_SIZE; i+=1){
		p_buff->u8[i] = buff[i];
	}

	if(p_buff->u16.sync != PIXY_START_WORD || p_buff->u16.sync != PIXY_START_WORD_CC){
		printf("error with block sync bytes\n\r");
		return 0;
	}
	return 1;
}

/*
 * for testing
 * print pixy data
 * */
void pixy_print(union pixy_data_union *p){
	printf("\n\r\n\r");
	printf("id: %" PRIu16"\n\r", p[0].u16.id);
	printf("x: %" PRIu16"\n\r", p[0].u16.x);
	printf("y: %" PRIu16"\n\r", p[0].u16.y);
	printf("width: %" PRIu16"\n\r", p[0].u16.width);
	printf("height: %" PRIu16"\n\r", p[0].u16.height);
}

void pixy_read_multiple(uint8_t *r_buff, union pixy_data_union *p, int obj_count){

	if (process_pixy_obj(r_buff, &p[0])){
		pixy_print(&p[0]);
	}

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
	MSS_I2C_read(&g_mss_i2c1, PIXY_I2C_DEFAULT_ADDR, receive_buf.u8, sizeof(receive_buf), MSS_I2C_RELEASE_BUS);
	MSS_TIM1_clear_irq();
}


int main(void)
{
	union pixy_data_union pixy_data[PIXY_OBJECT_COUNT];

	MSS_I2C_init(&g_mss_i2c1 , PIXY_I2C_DEFAULT_ADDR, MSS_I2C_PCLK_DIV_256 );
	start_hardware_cont_timer();

	while(1){
		switch(MSS_I2C_get_status(&g_mss_i2c1)){
		case MSS_I2C_SUCCESS:
			printf("%x%x",receive_buf.u16[0], receive_buf.u16[1]);
			//pixy_read_multiple(receive_buf.u8, pixy_data, PIXY_RECIEVE_BUFF_SIZE);
			break;

		case MSS_I2C_IN_PROGRESS:
		case MSS_I2C_FAILED:
		case MSS_I2C_TIMED_OUT:
		default:
			printf("i2c transmission issues %x\n\r", MSS_I2C_get_status(&g_mss_i2c1));
		}
	}
}

