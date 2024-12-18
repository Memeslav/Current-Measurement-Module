#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "Register.h"

typedef struct
{
	Register_32b_t global_impulse_counter;
	Register_32b_t num_of_last_read_impulse;
	Register_32b_t show_pulse_with_num;
}
Controls_t;

#endif
