/*
 * encoders.h
 *
 *  Created on: Apr 16, 2017
 *      Author: baldeeb
 */

#ifndef ENCODERS_H_
#define ENCODERS_H_


#include "main.h"

int prev_left_encoder_val = 0;
int prev_right_encoder_val = 0;
int left_wheel_tot = 0;
int right_wheel_tot = 0;

int left_encoder_val = 0;
int right_encoder_val = 0;
int left_rotating = 0;
int right_rotating = 0;

void update_encoder_vals( void ){

	prev_left_encoder_val = left_encoder_val;
	prev_right_encoder_val = right_encoder_val;

	if(*ENCODERS == 1 || *ENCODERS == 3)
		left_encoder_val = 1;
	else
		left_encoder_val = 0;

	if(*ENCODERS == 2 || *ENCODERS == 3)
		right_encoder_val = 1;
	else
		right_encoder_val = 0;

	// increment totals only when encoder is rotating
	if((prev_left_encoder_val == 0 && left_encoder_val == 1) || (prev_left_encoder_val == 1 && left_encoder_val == 0)){
		left_wheel_tot += 1;
		left_rotating = 1;
	}
	else{
		//do nothing
		//left_rotating = 0;
	}

	if((prev_right_encoder_val == 0 && right_encoder_val == 1) || (prev_right_encoder_val == 1 && right_encoder_val == 0)){
		right_wheel_tot += 1;
		right_rotating = 1;
	}
	else{
		//do nothing
		//right_rotating = 0;
	}
}

#endif /* ENCODERS_H_ */
