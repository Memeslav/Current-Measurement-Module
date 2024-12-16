#include "main.h"

int main(void)
{
	Module_ADC_Enable();

    while (1)
    {
    	for(int i = 0; i < 500; i++);

    	Module_ADC_Measure();
    	Module_ADC_Data_Processing();
    }
}
