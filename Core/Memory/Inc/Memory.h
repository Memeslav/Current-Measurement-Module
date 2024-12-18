#ifndef MEMORY_H_
#define MEMORY_H_

#include "Registers.h"
#include "Impulse_archive.h"

extern	volatile	Register_map_t 		registers;
extern 	volatile 	Impulse_archive_t 	impulse_archive;

void Memory_Init(void);

#endif
