#include "main.h"
#include "Module_ADC.h"

int32_t counter = 0;
int32_t sum = 0;
int32_t average = 0;
uint32_t delay = 1000;

int main(void)
{
	Module_ADC_Enable();

    while (1)
    {
    	for(int i = 0; i < delay; i++);
    	Module_ADC_Update();
    	counter++;

    	sum += SIGNAL;

    	average = sum / counter;
    }
}
