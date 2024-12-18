#include "Memory.h"

volatile	Register_map_t 		registers 		= {0};
volatile 	Impulse_archive_t 	impulse_archive = {0};

void Memory_Init(void)
{
	registers 		= (Register_map_t)		{0};
	impulse_archive = (Impulse_archive_t)	{0};
}
