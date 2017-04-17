/*
 * main.h
 *
 *  Created on: Apr 16, 2017
 *      Author: baldeeb
 */

#ifndef MAIN_H_
#define MAIN_H_

int * MOTOR_INPUTS = (int*) 0x40050004;
int * LEFT_MOTOR = (int*) 0x40050008;
int * RIGHT_MOTOR = (int*) 0x4005000C;
int * ENCODERS = (int*) 0x40050010;

const int PERIOD = 400000;
const int MAX_PWM = 400000;
/*const double Kp = 0.5;
const double Ki = 0.05;
const double Kd = 10.0;*/
const double Kp = 0.1;
const double Ki = 0.0001;
const double Kd = 4.5;

const int buff_size = 8;

int right_wheel_direction = 0;
int left_wheel_direction = 0;
int mode = 1;
float left_duty_cycle = 0;
float right_duty_cycle = 0;
float prev_right_duty_cycle = 0;
float prev_left_duty_cycle = 0;

#endif /* MAIN_H_ */
