#include "main.h"

uint16_t* 	regs 		= (uint16_t*)&registers;

uint16_t size = 0;

uint16_t test = 0;

uint32_t boop = 0;

Impulse_t imp = {0};

int main(void)
{
    Memory_Init();

    size = sizeof(registers);

    for(int i = 0; i < 32; i++)
	{
		regs[i] = i;
	}

    for(int i = 0; i < 32; i++)
    {
    	test = regs[i];
    }

    Memory_Init();

    while (1)
    {
    	Register_32b_Set(&imp.number, boop);
    	Register_32b_Set(&imp.start_time, boop);
    	Register_32b_Set(&imp.duration, boop);
    	imp.max_amp = boop;
    	imp.ave_amp = boop;

    	Impulse_Archive_Set_Impulse(&impulse_archive, &imp);

    	boop++;

    	registers.impulse = *Impulse_Archive_Get_Impulse(&impulse_archive, boop);

    	Register_32b_Increment(&registers.controls.global_impulse_counter);
    	Register_32b_Increment(&registers.controls.num_of_last_read_impulse);
    	Register_32b_Increment(&registers.controls.show_pulse_with_num);
    }
}
