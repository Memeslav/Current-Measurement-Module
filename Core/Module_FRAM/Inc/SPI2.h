#ifndef SPI2_H_
#define SPI2_H_

#include "stm32l053xx.h"

void SPI2_Enable(void);

static inline void SPI2_CS_L(void)	{GPIOB->BSRR = GPIO_BSRR_BR_12;}
static inline void SPI2_CS_H(void)	{GPIOB->BSRR = GPIO_BSRR_BS_12;}

uint8_t SPI2_Send_Byte(uint8_t data);

#endif
