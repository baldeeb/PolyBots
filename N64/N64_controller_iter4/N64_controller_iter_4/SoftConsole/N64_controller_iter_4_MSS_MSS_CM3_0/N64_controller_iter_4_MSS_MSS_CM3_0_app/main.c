#include "drivers/mss_uart/mss_uart.h"
#include "inttypes.h"
#include <stdio.h>
#include <stdlib.h>


#define CONTROLLER_DATA_REG ((uint32_t *) FPGA_FABRIC_BASE)

#define max_axis_thres 127
#define max_speed_percent 100
#define min_duty_cycle 30
#define max_duty_cylce 90

#define y_mask 0xFF000000
#define	x_mask 0x00FF0000
#define	up_mask 0x00000010
#define down_mask 0x00000020
#define	left_mask 0x00000040
#define	right_mask 0x00000080

int8_t change_endianness(int8_t old);
uint8_t calc_speed_percent_stick(uint8_t abs_x, uint8_t abs_y);
void parse_controller_data(uint32_t controller_data_local, uint8_t controller_buff[6]);
uint8_t calc_left_wheel_duty_cycle(int8_t x_axis, int8_t y_axis, uint8_t speed_percentage);
uint8_t calc_right_wheel_duty_cycle(int8_t x_axis, int8_t y_axis, uint8_t speed_percentage);
uint8_t calc_wheel_direction(int8_t y_axis);

int main(void)
{
	uint32_t controller_data; //holds all 32 bits of controller data

	float speed_percent;

	uint8_t right_wheel_duty_cycle;
	uint8_t left_wheel_duty_cycle;

	uint8_t right_wheel_direction; //0 -> stopped, 1 -> forward, 2 -> backward
	uint8_t left_wheel_direction; //0 -> stopped, 1 -> forward, 2 -> backward

	int relevant_data_bytes = 4;
	uint8_t controller_buff[relevant_data_bytes];
	uint8_t tx_buff[relevant_data_bytes];

	MSS_UART_init(
			&g_mss_uart1,
			MSS_UART_57600_BAUD,
			MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
	);

	while( 1 )
	{
		controller_data = *CONTROLLER_DATA_REG;

		parse_controller_data(controller_data, controller_buff); //fills in controller_buff with data from buttons/stick


		//calc speed percentage
		//check if Dpad is pressed -> if no, use analog stick coordinates, otherwise 100% for dPad 
		speed_percent = (!controller_buff[2] && !controller_buff[3] && !controller_buff[4] && !controller_buff[5] )  
				?
				calc_speed_percent_stick(abs(controller_buff[1]), abs(controller_buff[0])) :
				max_speed_percent;

		right_wheel_duty_cycle = calc_right_wheel_duty_cycle(controller_buff[1], controller_buff[0], speed_percent);
		left_wheel_duty_cycle = calc_left_wheel_duty_cycle(controller_buff[1], controller_buff[0], speed_percent);

		right_wheel_direction = calc_wheel_direction(controller_buff[0]);
		left_wheel_direction = calc_wheel_direction(controller_buff[0]);

		tx_buff[0] = right_wheel_duty_cycle;
		tx_buff[1] = right_wheel_direction;
		tx_buff[2] = left_wheel_duty_cycle;
		tx_buff[3] = left_wheel_direction;

		MSS_UART_polled_tx(&g_mss_uart1, tx_buff, sizeof(tx_buff));

		//printf("Controller Data: %" PRIu32 "\n",controller_buff);

	}

	return 0;
}


int8_t change_endianness(int8_t old) {
	int8_t new = 0;
	int i;
	for(i = 0; i < 8; i++) {
		new = new + ((0b00000001 &(old>>(7-i)))<< i);
	}
	return new;
}

float calc_speed_percent_stick(uint8_t abs_x, uint8_t abs_y) {
	uint8_t speed_percentage;
	if(abs_x >= max_axis_thres && abs_y >= max_axis_thres) {
		speed_percentage =  max_speed_percent;
	}
	else if(abs_x >= max_axis_thres) {
		speed_percentage = (float)abs_y/max_axis_thres;
		speed_percentage = (speed_percentage > 0) ? speed_percentage : max_speed_percent;
	}
	else if(abs_y >= max_axis_thres) {
		speed_percentage = (float)abs_x/max_axis_thres;
		speed_percentage = (speed_percentage > 0) ? speed_percentage : max_speed_percent;
	}
	else {
		speed_percentage = (float)(abs_x + abs_y)/(2*max_axis_thres);
	}
	return speed_percentage;
}

void parse_controller_data(uint32_t controller_data_local, uint8_t controller_buff[6]) {

	int8_t y_axis; //all 8 bits hold data about y_axis data from controller
	int8_t x_axis; //all 8 bits hold data about x_axis data from controller
	uint8_t up; //1 or 0
	uint8_t down; //1 or 0
	uint8_t left; //1 or 0
	uint8_t right; //1 or 0

	y_axis = (int8_t)((controller_data_local & y_mask) >> 24);
	y_axis = change_endianness(y_axis);

	x_axis = (int8_t)((controller_data_local & x_mask) >> 16);
	x_axis = change_endianness(x_axis);

	up = (uint8_t)((controller_data_local & up_mask) >> 4);
	down = (uint8_t)((controller_data_local & down_mask) >> 5);
	left = (uint8_t)((controller_data_local & left_mask) >> 6);
	right =(uint8_t)((controller_data_local & right_mask) >> 7);

	controller_buff[0] = y_axis;
	controller_buff[1] = x_axis;
	controller_buff[2] = up;
	controller_buff[3] = down;
	controller_buff[4] = left;
	controller_buff[5] = right;

}

uint8_t calc_left_wheel_duty_cycle(int8_t x_axis, int8_t y_axis, uint8_t speed_percentage) {
	float duty_cycle;
	if(x_axis > 0) {
		duty_cycle = speed_percentage * x_axis/max_axis_thres;
		duty_cycle = (duty_cycle > min_duty_cycle) ? duty_cycle : min_duty_cycle;
	}
	else if(x_axis < 0) {
		duty_cycle = min_duty_cycle;
	}
	else if(x_axis == 0) {
		duty_cycle = (y_axis == 0) ? 0 : speed_percentage * max_duty_cycle;
	}

	return (uint8_t) duty_cycle;
}

uint8_t calc_right_wheel_duty_cycle(int8_t x_axis, int8_t y_axis, uint8_t speed_percentage) {
	float duty_cycle;
	if(x_axis < 0) {
		duty_cycle = speed_percentage * x_axis/max_axis_thres;
		duty_cycle = (duty_cycle > min_duty_cycle) ? duty_cycle : min_duty_cycle;
	}
	else if(x_axis > 0) {
		duty_cycle = min_duty_cycle;
	}
	else if(x_axis == 0) {
		duty_cycle = (y_axis == 0) ? 0 : speed_percentage * max_duty_cycle;
	}

	return (uint8_t) duty_cycle;
}

uint8_t calc_wheel_direction(int8_t y_axis) {
	if(y_axis > 0) {
		return 1;
	}
	else if(y_axis < 0) {
		return 2;
	}
	else {
		return 0;
	}
}

