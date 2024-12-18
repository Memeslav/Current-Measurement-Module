#ifndef IMP_ARCHIVE_H_
#define IMP_ARCHIVE_H_

#include <Impulse.h>

#define IMPULSE_ARCHIVE_SIZE 128

typedef struct
{
	IMPULSE impulse[IMPULSE_ARCHIVE_SIZE];
}
IMPULSE_ARCHIVE;

extern volatile IMPULSE_ARCHIVE impulse_archive;
extern uint16_t* impulses;

void Save_Impulse_to_Archive(IMPULSE* impulse);

#endif
