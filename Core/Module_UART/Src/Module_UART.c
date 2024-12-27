#include "Module_UART.h"

/*
void Module_UART_Init	(	uint32_t baudrate	)
{

}

void Module_UART_Send	(	uint8_t* data,
							uint16_t size	)
{

}

void DMA1_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
	    DMA1_Channel2->CPAR = (uint32_t)&USART1->TDR;
	    DMA1_Channel2->CMAR = (uint32_t)buffer;
	    DMA1_Channel2->CNDTR = sizeof(buffer);
	    DMA1_Channel2->CCR |= DMA_CCR_MINC;
	    DMA1_Channel2->CCR |= DMA_CCR_DIR;
}

void USART1_Init(uint32_t baudrate)
{
	SystemCoreClockUpdate();

		baudrate = (baudrate == 0) ? 9600 : baudrate;

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

		GPIOA->MODER &= ~(GPIO_MODER_MODE9_0 |
						  GPIO_MODER_MODE10_0);

		GPIOA->AFR[1] |= (0b0100 << GPIO_AFRH_AFSEL9_Pos |
						  0b0100 << GPIO_AFRH_AFSEL10_Pos);

	DMA1_Init();

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		USART1->BRR  = SystemCoreClock/baudrate;

		USART1->CR3  = 	USART_CR3_DMAT;
		USART1->CR2  = 	0;
		USART1->CR1 |= 	USART_CR1_TE
					| 	USART_CR1_UE;
}

void USART1_Send_Data(void)
{
	DMA1_Channel2->CCR |= DMA_CCR_EN;
}

void DMA1_Channel2_3_IRQHandler(void)
{

}
*/
