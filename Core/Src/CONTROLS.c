#include "CONTROLS.h"

void Global_Counter_Increment(volatile CONTROLS* controls)
{
	controls->global_counter_lo += 1;

    if (controls->global_counter_lo == 0)
    {
    	controls->global_counter_hi += 1;
    }
}
