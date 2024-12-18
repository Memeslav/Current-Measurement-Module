#ifndef IMP_ARCHIVE_H_
#define IMP_ARCHIVE_H_

#include "Impulse.h"

#define IMPULSE_ARCHIVE_SIZE 128

typedef struct
{
	Impulse_t impulse[IMPULSE_ARCHIVE_SIZE];
}
IMPULSE_ARCHIVE;

#endif
