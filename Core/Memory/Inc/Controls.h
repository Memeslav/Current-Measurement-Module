#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "Register.h"

typedef struct
{
	Register_32b_t global_counter;
	Register_32b_t last_readed;
	Register_32b_t show_pulse;
}
CONTROLS;

#endif
