#ifndef SPI_H_
#define SPI_H_

#include "stm32l053xx.h"
#include "DMA.h"

#define FRAM_TIMEOUT 1000

void SPI1_Enable(void);
void SPI2_Enable(void);

void SPI2_CS_HIGH(void);
void SPI2_CS_LOW (void);

uint8_t SPI2_Transfer_Byte(uint8_t byte);

#endif
