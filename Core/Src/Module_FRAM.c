#include "Module_FRAM.h"

#define	CS_LOW	(GPIOB->BSRR |= GPIO_BSRR_BR_12);
#define	CS_HIG	(GPIOB->BSRR |= GPIO_BSRR_BS_12);

void Module_FRAM_Enable(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

		SPI2->CR2  =  0;

		SPI2->CR1  =  SPI_CR1_MSTR|
					  SPI_CR1_SPE |
					  SPI_CR1_SSM |
					  SPI_CR1_SSI ;

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
void Module_FRAM_Disable(void)
{
	RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;

	RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;

		GPIOB->MODER |=   GPIO_MODER_MODE12_Msk|
						  GPIO_MODER_MODE13_Msk|
						  GPIO_MODER_MODE14_Msk|
						  GPIO_MODER_MODE15_Msk;
}


static uint8_t SendByte (uint8_t data)
{
	while (!(SPI2->SR & SPI_SR_TXE));
	SPI2->DR = data;

	while (!(SPI2->SR & SPI_SR_RXNE));
	return SPI2->DR;
}

void FRAM_READ (uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	CS_LOW;

	SendByte(READ);

	SendByte((address >> 8) & 0xFF);
	SendByte(address & 0xFF);

	for(uint16_t i = 0; i < data_size; i++)
	{
		data[i] = SendByte(0x00);
	}

	CS_HIG;
}

void FRAM_WRITE(uint16_t address,
				uint16_t data_size,
				uint8_t* data)
{
	CS_LOW;
	SendByte(WREN);
	CS_HIG;

	CS_LOW;

	SendByte(WRITE);

	SendByte((address >> 8) & 0xFF);
	SendByte(address & 0xFF);

	for(uint16_t i = 0; i < data_size; i++)
	{
		SendByte(data[i]);
	}

	CS_HIG;
}

void LOAD_REGISTERS_TO_FRAM(void)
{
	Module_FRAM_Enable();

	FRAM_WRITE(0, sizeof(SETTINGS), (uint8_t*)&registers.settings);

	Module_FRAM_Disable();
}
void LOAD_REGISTERS_FROM_FRAM(void)
{
	Module_FRAM_Enable();

	FRAM_READ(0, sizeof(SETTINGS), (uint8_t*)&registers.settings);

	Module_FRAM_Disable();
}
