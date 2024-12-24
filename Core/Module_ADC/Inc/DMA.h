#ifndef DMA1_H_
#define DMA1_H_

#include "stm32l053xx.h"

void DMA_Enable(volatile uint32_t* from, volatile uint32_t* to, uint8_t size);

static inline void DMA_Waiting_Transmission(void)	{	while (!(DMA1->ISR & DMA_ISR_TCIF1)){}
														DMA1->IFCR |= DMA_IFCR_CHTIF1;	}

#endif
