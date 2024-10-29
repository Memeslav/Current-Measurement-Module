#include "main.h"

int main(void)
{
	LED_Enable(RED);
	LED_Enable(GRN);
	LED_Enable(BLU);
	LED_Enable(YEL);

	LED_Disable(RED);
	LED_Disable(GRN);
	LED_Disable(BLU);
	LED_Disable(YEL);

	LED_Toggle(RED);
	LED_Toggle(GRN);
	LED_Toggle(BLU);
	LED_Toggle(YEL);


    while (1)
    {
    }
}
