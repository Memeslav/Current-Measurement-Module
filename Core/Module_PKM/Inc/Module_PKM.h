#ifndef MODULE_PKM_H_
#define MODULE_PKM_H_

#include "CRC.h"
#include "SPI1.h"
#include "Memory.h"

#define PKM_BUFFER_SIZE  	32U
#define PKM_COMMAND_MASK 	0x0001
#define PKM_ADDRESS_MASK 	0x7FFF

typedef enum	{	RECEIVE_DATA	= 0,
					TRANSMIT_DATA	= 1,	}	PKM_command;

typedef struct
{
	PKM_command command;

    uint16_t data[PKM_BUFFER_SIZE];
    uint16_t index;

    uint16_t start_address;
    uint16_t register_count;
}
PKM_buffer_t;

static inline void Module_PKM_Enable(void)	{CRC_Enable(); SPI1_Enable();};

#endif
