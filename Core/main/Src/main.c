#include "main.h"

#include "Current_handler.h"

#include "Impulse_handler.h"

Impulse_handler_t murr = {0};

Current_handler_buffer_t meow = {0};

uint16_t max, ave, min;

int main(void)
{
	Current_handler_reset(&meow);

	Impulse_handler_set_trigger(&murr, 2200, 100);

	for(int i = 1; i <= 10000; i++){Current_handler_update(&meow, i);}

	max = Current_handler_get_maximal(&meow);
	ave = Current_handler_get_average(&meow);
	min = Current_handler_get_minimal(&meow);

	Current_handler_reset(&meow);

    while (1)
    {

    }
}
