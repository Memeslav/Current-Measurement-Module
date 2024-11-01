#ifndef DMA_H_
#define DMA_H_

#include "stm32l053xx.h"

void DMA1_Init(void);

void DMA1_Ch_1(uint32_t* src_address, uint32_t* dest_address, uint32_t num_data);

#endif
