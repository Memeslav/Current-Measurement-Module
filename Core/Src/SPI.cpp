#include "SPI.hpp"

_SPI::_SPI(SPI_TypeDef* SPI_ID) : SPI_ID(SPI_ID)
{
    if	(SPI_ID == SPI1)
    {

    }
    else if (SPI_ID == SPI2)
    {
    	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

			SPI2->CR2  =  0;

			SPI2->CR1  =  SPI_CR1_MSTR | SPI_CR1_SPE | SPI_CR1_SSM | SPI_CR1_SSI;

		RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;

			GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk | GPIO_MODER_MODE13_Msk |
							  GPIO_MODER_MODE14_Msk | GPIO_MODER_MODE15_Msk);

			GPIOB->MODER |=  (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_1 |
							  GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1);
    }
}

void _SPI::low_CS(void)
{
	if		(SPI_ID == SPI1){}
	else if (SPI_ID == SPI2){GPIOB->BSRR |= GPIO_BSRR_BR_12;}
}

void _SPI::hig_CS(void)
{
	if		(SPI_ID == SPI1){}
	else if (SPI_ID == SPI2){GPIOB->BSRR |= GPIO_BSRR_BS_12;}
}

uint8_t _SPI::transfer_byte(uint8_t byte)
{
	while (!(SPI_ID->SR & SPI_SR_TXE));
	SPI_ID->DR = byte;

	while (!(SPI_ID->SR & SPI_SR_RXNE));
	return SPI_ID->DR;
}
