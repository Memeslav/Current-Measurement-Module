#include "SPI2.h"

void SPI2_Enable(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

		SPI2->CR2  =  0;

		SPI2->CR1  =  SPI_CR1_SPE |
					  SPI_CR1_SSM |
					  SPI_CR1_SSI |
					  SPI_CR1_MSTR;

	RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;

		GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk|
						  GPIO_MODER_MODE13_Msk|
						  GPIO_MODER_MODE14_Msk|
						  GPIO_MODER_MODE15_Msk);

		GPIOB->MODER |=   GPIO_MODER_MODE12_0|
						  GPIO_MODER_MODE13_1|
						  GPIO_MODER_MODE14_1|
						  GPIO_MODER_MODE15_1;
}

uint8_t SPI2_Send_Byte(uint8_t data)
{
	while (!(SPI2->SR & SPI_SR_TXE));
	SPI2->DR = data;

	while (!(SPI2->SR & SPI_SR_RXNE));
	return SPI2->DR;
}
