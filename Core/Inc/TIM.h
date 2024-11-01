#ifndef TIM_H_
#define TIM_H_

#include "stm32l053xx.h"

void TIM21_Init 	(void);
void TIM21_Enable	(void);
void TIM21_Disable	(void);

void TIM7_Enable	(uint16_t time_ms);
void TIM7_Disable	(void);

#endif
