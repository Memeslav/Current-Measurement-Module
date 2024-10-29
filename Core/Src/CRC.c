#include "CRC.h"

void CRC_Enable(void)
{
	RCC->AHBENR |= RCC_AHBENR_CRCEN;

		CRC->CR |= CRC_CR_RESET;
		CRC->CR |= CRC_CR_REV_OUT;
		CRC->CR |= CRC_CR_REV_IN_0;
		CRC->CR |= CRC_CR_POLYSIZE_0;

		CRC->POL  = 0x8005;
		CRC->INIT = 0xFFFF;
}

void CRC_Reset (void)
{
	CRC->CR |= CRC_CR_RESET;
}