#include "SPI.h"

void SPI1_Enable(void)
{
    RCC->IOPENR   |= RCC_IOPENR_GPIOAEN;

    	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk |
				  	      GPIO_MODER_MODE5_Msk |
					      GPIO_MODER_MODE6_Msk |
					      GPIO_MODER_MODE7_Msk);

		GPIOA->MODER |=	 (GPIO_MODER_MODE4_1 |
					  	  GPIO_MODER_MODE5_1 |
					      GPIO_MODER_MODE6_1 |
					      GPIO_MODER_MODE7_1);

		EXTI->IMR 	 |=   EXTI_IMR_IM4;
		EXTI->RTSR   |=   EXTI_RTSR_RT4;
		EXTI->FTSR   |=   EXTI_FTSR_FT4;

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

    RCC->APB2ENR  |= RCC_APB2ENR_SPI1EN;

    	SPI1->CR2  = SPI_CR2_RXNEIE;

		SPI1->CR1  = SPI_CR1_SPE |
				     SPI_CR1_DFF |
					 SPI_CR1_CPOL|
					 SPI_CR1_CPHA;

	NVIC_SetPriority(SPI1_IRQn, 0);
	NVIC_EnableIRQ(SPI1_IRQn);
}

void SPI2_Enable(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

		SPI2->CR2  =  0;

		SPI2->CR1  =  SPI_CR1_SSI |
					  SPI_CR1_SPE |
					  SPI_CR1_SSM |
					  SPI_CR1_MSTR;

	RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;

		GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk |
						  GPIO_MODER_MODE13_Msk |
						  GPIO_MODER_MODE14_Msk |
						  GPIO_MODER_MODE15_Msk);

		GPIOB->MODER |=  (GPIO_MODER_MODE12_0 |
						  GPIO_MODER_MODE13_1 |
						  GPIO_MODER_MODE14_1 |
						  GPIO_MODER_MODE15_1);
}

void SPI2_CS_HIGH(void)
{
	GPIOB->BSRR |= GPIO_BSRR_BS_12;
}

void SPI2_CS_LOW (void)
{
	GPIOB->BSRR |= GPIO_BSRR_BR_12;
}

uint8_t SPI2_Transfer_Byte(uint8_t byte)
{
	uint32_t timeout = FRAM_TIMEOUT;

	while (!(SPI2->SR & SPI_SR_TXE))
	{if(--timeout == 0){return 0xFF;}}
	SPI2->DR = byte;

	while (!(SPI2->SR & SPI_SR_RXNE))
	{if(--timeout == 0){return 0xFF;}}
	return SPI2->DR;
}
