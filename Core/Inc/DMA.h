#ifndef DMA_H_
#define DMA_H_

#include "stm32l053xx.h"

void DMA1_Ch_1_Enable(volatile void* data_collector, uint8_t data_size);

#endif
