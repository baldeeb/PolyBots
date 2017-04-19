
/*
 * followProcessing.h
 *
 *  Created on: Apr 17, 2017
 *      Author: liujiayi
 */

#ifndef FOLLOWPROCESSING_H_
#define FOLLOWPROCESSING_H_

#include "pixy.h"
#include "IRcontrol.h"

int rmotor_pwm ;
int lmotor_pwm ;
int motor_dir ;

int update_flag;

#define PERIOD 400000
#define MAX_PWM 400000

#define IR_PWM_CONTRIBUTION 0.25
#define PIXY_PWM_CONTRIBUTION  MAX_PWM*0.03
#define LEFT_MOTOR_CORRECTION 1//0.95
#define RIGHT_MOTOR_CORRECTION 1//1.05


void init_motor_commends( void ){
	rmotor_pwm = 0;
	lmotor_pwm = 0;
	motor_dir = 0;
}


void get_motor_command(int * rpwm, int * lpwm, int * dir){

	unsigned int pixy_mag, pixy_dir;
	int pixy_pwm = 0 ;

	//return if data is none existant
	ir_update_error();
	if(!pixy_x_err( &pixy_mag, &pixy_dir)){ return; }

	pixy_pwm = PIXY_PWM_CONTRIBUTION * pixy_mag;
	dir[0] = pixy_dir;

	if(pixy_dir == 1){
		//if turning left
		if(ir_dir == 1)	{
			*lpwm = pixy_pwm + (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
			*rpwm = pixy_pwm  - (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
			//*rpwm = pixy_pwm  - (IR_PWM_CONTRIBUTION * ir_error);
		}
		//if turning right
		else if(ir_dir == 2) {
			*rpwm = pixy_pwm + (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
			*lpwm = pixy_pwm - (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
		}
		else{
			*rpwm = pixy_pwm;//temp;
			*lpwm = pixy_pwm;//temp;
		}
	}
	else if(pixy_dir == 2){
		//if turning left
		if(ir_dir == 1)	{
			*lpwm = LEFT_MOTOR_CORRECTION * (pixy_pwm - (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error));
			*rpwm = pixy_pwm + (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
		}
		//if turning right
		else if(ir_dir == 2) {
			*rpwm = pixy_pwm - (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error);
			*lpwm = LEFT_MOTOR_CORRECTION * (pixy_pwm + (pixy_pwm * IR_PWM_CONTRIBUTION * ir_error)) ;
		}
		else{
			*rpwm = pixy_pwm;//temp;
			*lpwm = LEFT_MOTOR_CORRECTION * pixy_pwm;//temp;
		}
	}
	else { // no direction, don't move
		if(ir_dir == 1)	{
			*lpwm = 0;
			*rpwm  = ir_error * IR_PWM_CONTRIBUTION * MAX_PWM;
		}
		else if(ir_dir == 2) {
			*lpwm = ir_error * IR_PWM_CONTRIBUTION * MAX_PWM;
			*rpwm  = 0;
		}
		else{
			*lpwm = 0;
			*rpwm  = 0;
		}

		//todo: remove!
		*lpwm = 0; // temp
		*rpwm  = 0;// temp
	}

	if (*rpwm > 500000){*rpwm = 500000;}
	else if(*rpwm < 0 ){*rpwm = 0;}
	if (*lpwm > 500000){*lpwm = 500000;}
	else if(*lpwm < 0 ){*lpwm = 0;}


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
	update_flag = 1;
	update_pixy_data_flag = 1;
}

#endif /* FOLLOWPROCESSING_H_ */
