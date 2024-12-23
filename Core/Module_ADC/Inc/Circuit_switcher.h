#ifndef CIRCUIT_SWITCHER_H_
#define CIRCUIT_SWITCHER_H_

#include "stm32l053xx.h"

static inline void Circuit_Switcher_On	(void)	{	RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;
														GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
														GPIOB->MODER &=~GPIO_MODER_MODE2_1;
														GPIOB->BSRR  |= GPIO_BSRR_BS_2;}

static inline void Circuit_Switcher_Off	(void)	{		GPIOB->BSRR  |= GPIO_BSRR_BR_2;
													RCC->IOPENR  &=~RCC_IOPENR_GPIOBEN;}

#endif
