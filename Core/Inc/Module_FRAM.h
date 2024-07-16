#ifndef INC_MODULE_FRAM_H_
#define INC_MODULE_FRAM_H_

#include "stm32l053xx.h"
#include "Memory.h"

typedef enum
{
	WRITE = 0x02,
	READ  = 0x03,
	WREN  = 0x06,
}
FRAM_Commands;

void Module_FRAM_Enable(void);

void FRAM_READ (uint16_t address,
				uint16_t data_size,
				uint8_t* data);

void FRAM_WRITE(uint16_t address,
				uint16_t data_size,
				uint8_t* data);

void LOAD_REGISTERS_TO_FRAM(void);
void LOAD_REGISTERS_FROM_FRAM(void);

#endif
