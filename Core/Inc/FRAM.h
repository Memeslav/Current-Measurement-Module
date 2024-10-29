#ifndef FRAM_H_
#define FRAM_H_

#include "SPI.h"
#include "MEM.h"

#define FRAM_SIZE	8192U

typedef enum
{
	WREN	= 0x06,		// Set Write Enable Latch
	WRDI	= 0x04,		// Reset Write Enable Latch
	RDSR	= 0x05,		// Read Status Register
	WRSR	= 0x01,		// Write Status Register
	READ	= 0x03,		// Read Memory Code
	WRITE	= 0x02,		// Write Memory Code
}
MB85RS64PNF_CODE;

void FRAM_Enable(void);

void FRAM_READ (uint16_t address,
				uint16_t data_size,
				uint8_t* data);

void FRAM_WRITE(uint16_t address,
				uint16_t data_size,
				uint8_t* data);

void FRAM_Save_Settings(void);
void FRAM_Load_Settings(void);

#endif
