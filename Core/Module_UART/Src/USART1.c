#include "USART1.h"

void USART1_Init(uint32_t baudrate)
{
	SystemCoreClockUpdate();

	baudrate = (baudrate == 0) ? 9600 : baudrate;

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

		GPIOA->MODER &= ~(GPIO_MODER_MODE9_0 | GPIO_MODER_MODE10_0);

		GPIOA->AFR[1] |= (0b0100 << GPIO_AFRH_AFSEL9_Pos | 0b0100 << GPIO_AFRH_AFSEL10_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		USART1->BRR  = SystemCoreClock/baudrate;

		USART1->CR3  = 0;

		USART1->CR2  = 0;

		USART1->CR1 |= USART_CR1_TE | USART_CR1_UE;
}
