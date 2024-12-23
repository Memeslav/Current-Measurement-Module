#include "main.h"

#include "Current_handler.h"
#include "Impulse_handler.h"

Impulse_handler_t imp;

Impulse_t	booper = {.average = 1, .maximal = 2, .start = 1, .end = 3};

int main(void)
{
	Impulse_Handler_Clear(&imp);
	Impulse_Handler_Set_Filter(&imp, 4);
	Impulse_Handler_Set_Trigger(&imp, 10, 2);

	Impulse_Handler_Update(&imp,  0,  0);
	Impulse_Handler_Update(&imp, 12,  1);
	Impulse_Handler_Update(&imp, 12,  2);
	Impulse_Handler_Update(&imp, 12,  3);
	Impulse_Handler_Update(&imp,  0,  4);

	Impulse_Handler_Clear(&imp);

	Impulse_Handler_Update(&imp,  0,  5);
	Impulse_Handler_Update(&imp, 15,  6);
	Impulse_Handler_Update(&imp, 15,  7);
	Impulse_Handler_Update(&imp, 15,  8);
	Impulse_Handler_Update(&imp, 15,  9);
	Impulse_Handler_Update(&imp, 15, 10);
	Impulse_Handler_Update(&imp, 15, 11);
	Impulse_Handler_Update(&imp,  0, 12);

	//Impulse_Handler_Clear(&imp);

	Impulse_Handler_Update(&imp,  0, 13);
	Impulse_Handler_Update(&imp, 13, 14);
	Impulse_Handler_Update(&imp, 13, 15);
	Impulse_Handler_Update(&imp, 13, 16);
	Impulse_Handler_Update(&imp,  0, 17);

	Impulse_Handler_Clear(&imp);

	Impulse_Handler_Update(&imp,  0, 18);
	Impulse_Handler_Update(&imp, 14, 19);
	Impulse_Handler_Update(&imp, 14, 20);
	Impulse_Handler_Update(&imp, 14, 21);
	Impulse_Handler_Update(&imp, 14, 22);
	Impulse_Handler_Update(&imp, 14, 23);
	Impulse_Handler_Update(&imp, 14, 24);
	Impulse_Handler_Update(&imp,  0, 25);

	Impulse_Handler_Clear(&imp);

	Impulse_Handler_Update(&imp,  0, 26);
	Impulse_Handler_Update(&imp, 16, 27);
	Impulse_Handler_Update(&imp, 16, 28);
	Impulse_Handler_Update(&imp, 16, 29);
	Impulse_Handler_Update(&imp, 16, 30);
	Impulse_Handler_Update(&imp,  0, 31);

	Impulse_Handler_Clear(&imp);

	while (1)
    {
    }
}
