#include "ADC.h"

volatile ADC_RAW_DATA ADC_DATA = {0, 0, 0, 0};

void ADC_Measure(ADC_RAW_DATA* ADC_DATA)
{
	//DMA_Enable((uint32_t*)ADC_DATA);
}



void ADC_COMP_IRQHandler(void)
{

}
