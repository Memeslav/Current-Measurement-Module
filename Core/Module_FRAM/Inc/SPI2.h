#ifndef SPI2_H_
#define SPI2_H_

#include "stm32l053xx.h"

void SPI2_Enable(void);

void SPI2_CS_L(void);
void SPI2_CS_H(void);

uint8_t SPI2_Send_Byte(uint8_t data);

#endif
