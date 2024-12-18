#ifndef CURRENTS_H_
#define CURRENTS_H_

#include "Register.h"

typedef struct
{
	Register_16b_t max;
	Register_16b_t ave;
	Register_16b_t min;
}
Currents_t;

static inline void Currents_Clear (Currents_t* currents)
{
	*currents = (Currents_t){0};
}

#endif
