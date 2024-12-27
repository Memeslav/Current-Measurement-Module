#include "main.h"

uint32_t counter = 0;
int16_t s = 4;

float volts_per_level = 0;

void Calculate_volts_per_level(void)
{
	volts_per_level = INTERNAL_REF / ADC1_DATA[INT_REF];
}

float Calculate_INA333S(uint16_t level)
{
	float ina333s = level * volts_per_level;

	return ina333s;
}

int main(void)
{
    Module_ADC_Init();
    Module_USART_Init(115200);

	Switch_Init();

    char buffer[1024];


    while (1)
    {
    	Switch_On();
    	for (int i = 0; i < 1000; i++);
        Module_ADC_Measure();
        Module_ADC_Measure();
        Module_ADC_Measure();
        Module_ADC_Measure();
        Module_ADC_Measure();
    	//for (int i = 0; i < 1000; i++);

    	Switch_Off();
        // Форматируем строку с очисткой экрана и перемещением курсора

        Calculate_volts_per_level();

        float v1 = volts_per_level * (ADC1_DATA[INA333S] - s);
        float v2 = volts_per_level * (ADC1_DATA[TPR3312]);
        float v3 = volts_per_level * (ADC1_DATA[INT_REF]);

        float t1 = Calculate_Temperature(ADC1_DATA[TEMPERC]);

        float s1 = 1000 * Calculate_INA333S(ADC1_DATA[INA333S] - s - ADC1_DATA[TPR3312]);

        sprintf(buffer,
                "\033[2J\033[H"
                "Measure %lu\r\n"
                "==================\r\n"
                "INA333S = %d L\r\n"
                "TPR3312 = %d L\r\n"
                "INT_REF = %d L\r\n"
                "TEMPERC = %d L\r\n"
                "==================\r\n"
                "INA333S = %.3f V\r\n"
                "TPR3312 = %.3f V\r\n"
                "INT_REF = %.3f V\r\n"
        		"TEMPERC = %.2f C\r\n"
        		"==================\r\n"
        		"SIGNAL = %.3f mV\r\n",
                counter++,
                ADC1_DATA[INA333S] - s,
                ADC1_DATA[TPR3312],
                ADC1_DATA[INT_REF],
                ADC1_DATA[TEMPERC],
                v1,
                v2,
                v3,
				t1,
				s1);


        // Отправляем строку через USART
        Module_USART_Transmit((uint8_t *)buffer, strlen(buffer));

        // Небольшая задержка перед следующим циклом
        for (int i = 0; i < 50000; i++);
    }
}
