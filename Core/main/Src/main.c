#include "main.h"

uint32_t counter = 0;

int main(void)
{
	USART1_Init(115200);

	uint16_t temp = 25;
	uint16_t humd = 60;

    while (1)
    {
    	USART1_Send_Formatted("Temperature: %dC, Humidity: %d%%\r", temp, humd);

    	temp++;
    	humd--;
    }
}
