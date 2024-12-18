#ifndef MEMORY_H_
#define MEMORY_H_

#include "Registers.h"
#include "Impulse_archive.h"

extern	volatile	REGISTERS 	registers;
extern 				uint16_t* 	regs;

extern 	volatile 	IMPULSE_ARCHIVE 	impulse_archive;
extern 				uint16_t* 			impulses;

void Memory_Init(void);

#endif
