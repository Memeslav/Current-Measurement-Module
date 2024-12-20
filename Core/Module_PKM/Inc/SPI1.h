#ifndef SPI1_H_
#define SPI1_H_

#include "stm32l053xx.h"

void SPI1_Enable (void);

static inline void SPI1_Send_16b_frame	(uint16_t frame)	{	SPI1->DR = frame;}

static inline void SPI1_MISO_Reset		(void)				{	GPIOA->MODER |= GPIO_MODER_MODE6_Msk;
																GPIOA->MODER &= ~GPIO_MODER_MODE6_0;}

static inline void SPI1_MISO_Set		(void)				{	GPIOA->MODER |= GPIO_MODER_MODE6_Msk;
																GPIOA->MODER &=	~GPIO_MODER_MODE6_1;
																GPIOA->BSRR |= GPIO_BSRR_BR_6;}

#endif
