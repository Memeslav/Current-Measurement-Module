#ifndef DMA_H_
#define DMA_H_

#include "stm32l053xx.h"

void DMA_Enable(volatile uint32_t* from, volatile uint32_t* to, uint8_t size);

#endif
