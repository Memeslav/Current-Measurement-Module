#ifndef MEMORY_H_
#define MEMORY_H_

#include "Registers.h"
#include "Impulse_archive.h"

extern	volatile	REGISTERS 			registers;
extern 	volatile 	IMPULSE_ARCHIVE 	impulse_archive;

void Memory_Init(void);

#endif
