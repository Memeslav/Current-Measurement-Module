#ifndef DMA_H_
#define DMA_H_

#include "stm32l053xx.h"

#define CxS_ADC		0b0000U
#define CxS_SPI2	0b0010U

void DMA1_Init(void);

void DMA1_Ch_4(uint32_t* data_target, uint32_t size);
void DMA1_Ch_5(uint32_t* data_source, uint32_t size);

#endif
