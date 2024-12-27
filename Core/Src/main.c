#include "main.h"

char test[] = "Test! \r\n";

int main(void)
{
	Module_USART_Init(9600);

    while (1)
    {
    	for(int i = 0; i < 100000; i++);

    	Module_USART_Transmit((uint8_t*)test, sizeof(test));
    	for(int i = 0; i < 100000; i++);
    }
}
