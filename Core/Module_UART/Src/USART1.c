#include "USART1.h"

static char buffer[USART1_BUFFER_SIZE] = {0};

void USART1_Init(uint32_t baudrate)
{
	SystemCoreClockUpdate();

		baudrate = (baudrate == 0) ? 9600 : baudrate;

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

		GPIOA->MODER &= ~(GPIO_MODER_MODE9_0 |
						  GPIO_MODER_MODE10_0);

		GPIOA->AFR[1] |= (0b0100 << GPIO_AFRH_AFSEL9_Pos |
						  0b0100 << GPIO_AFRH_AFSEL10_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		USART1->BRR  = SystemCoreClock/baudrate;

		USART1->CR3  = 	0;
		USART1->CR2  = 	0;
		USART1->CR1 |= 	USART_CR1_TE
					| 	USART_CR1_UE;
}

void USART1_Send_Byte(uint8_t byte)
{
    while (!(USART1->ISR & USART_ISR_TXE));
    USART1->TDR = byte;
}

void USART1_Send_Data(uint8_t* data, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		USART1_Send_Byte(data[i]);
	}
}

void USART1_Send_Formatted(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	memset(buffer, 0, sizeof(buffer));
	int length = vsnprintf(buffer, sizeof(buffer), format, args);

	va_end(args);

	if (length > 0 && length < sizeof(buffer))
	{
		USART1_Send_Data((uint8_t *)buffer, length);
	}
}
