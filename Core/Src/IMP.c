#include "IMP.h"

void Clear_Impulse(IMPULSE* impulse)
{
	impulse->num_lo 		= 0;
	impulse->num_hi 		= 0;

	impulse->start_time_lo 	= 0;
	impulse->start_time_hi 	= 0;

	impulse->duration_lo 	= 0;
	impulse->duration_hi 	= 0;

	impulse->max_amp 		= 0;
	impulse->ave_amp 		= 0;
}
