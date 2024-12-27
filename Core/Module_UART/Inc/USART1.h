#ifndef USART1_H_
#define USART1_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "stm32l053xx.h"

#define USART1_BUFFER_SIZE	128U

void USART1_Init(uint32_t baudrate);

void USART1_Send_Byte(uint8_t byte);
void USART1_Send_Data(uint8_t* data, uint16_t size);

void USART1_Send_Formatted(const char *format, ...);

#endif
