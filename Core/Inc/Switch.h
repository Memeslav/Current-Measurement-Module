#ifndef SWITCH_H_
#define SWITCH_H_

#include "stm32l053xx.h"

static inline void Switch_Init	(void)	{RCC->IOPENR  |= RCC_IOPENR_GPIOBEN;
										GPIOB->MODER |= GPIO_MODER_MODE2_Msk;
										GPIOB->MODER &=~GPIO_MODER_MODE2_1;}

static inline void Switch_On	(void)	{GPIOB->BSRR   |=  GPIO_BSRR_BS_2;}

static inline void Switch_Off	(void)	{GPIOB->BSRR  |=  GPIO_BSRR_BR_2;}

#endif
