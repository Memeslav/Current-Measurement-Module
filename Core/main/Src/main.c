#include "main.h"
#include "Driver_ADC.h"

ADC_t adc;
ADC_Level_t meme[4] = {0};

ADC_Level_t boop = 0;

int main(void)
{
	ADC_Init(&adc);

	while (1)
    {
		adc.measure();
		boop = adc.get_channel(INA333S);
    }
}
