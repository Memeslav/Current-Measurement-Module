#ifndef IMP_ARCHIVE_H_
#define IMP_ARCHIVE_H_

#include "Impulse.h"

#define IMPULSE_ARCHIVE_SIZE 128

typedef struct
{
	Impulse_t impulse[IMPULSE_ARCHIVE_SIZE];
}
Impulse_archive_t;

static inline void Impulse_Archive_Save_Impulse(volatile Impulse_archive_t* archive, const Impulse_t* impulse)
{
	uint32_t index = Register_32b_Get(&impulse->number);
    archive->impulse[index % IMPULSE_ARCHIVE_SIZE] = *impulse;
}

static inline const volatile Impulse_t* Impulse_Archive_Get_Impulse(const volatile Impulse_archive_t* archive, uint32_t number)
{
	uint32_t index = number % IMPULSE_ARCHIVE_SIZE;
	return &archive->impulse[index];
}

#endif
