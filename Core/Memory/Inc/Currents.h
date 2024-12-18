#ifndef CURRENTS_H_
#define CURRENTS_H_

#include "Register.h"

typedef struct
{
	Register_16b_t max;
	Register_16b_t ave;
	Register_16b_t min;
}
CURRENTS;

static	inline	void	Currents_Clear	(CURRENTS* currents)	{*currents = (CURRENTS){0};}

#endif
