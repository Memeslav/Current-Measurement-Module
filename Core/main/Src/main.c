#include "main.h"
#include "Driver_ADC.h"

uint32_t times = 0;

ADC_t adc;
ADC_Level_t meme[4] = {0};

int main(void)
{
	ADC_Init(&adc);

	while (1)
    {
		adc.measure();
		adc.get_all_channels(meme);

		times++;
    }
}
