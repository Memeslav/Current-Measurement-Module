#ifndef IMPULSE_H_
#define IMPULSE_H_

#include "Register.h"

typedef struct
{
	Register_32b_t number;

	Register_32b_t start_time;
	Register_32b_t duration;

	Register_16b_t max_amp;
	Register_16b_t ave_amp;
}
Impulse_t;

static inline void Impulse_Clear (Impulse_t* impulse)
{
	*impulse = (Impulse_t){0};
}

#endif
