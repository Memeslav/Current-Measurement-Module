#include "IMP_ARCHIVE.h"

volatile IMPULSE_ARCHIVE impulse_archive = {0};
uint16_t* impulses = (uint16_t*)&impulse_archive;

void Save_Impulse_to_Archive(IMPULSE* impulse)
{
	uint32_t impulse_number = (uint32_t)(impulse->num_hi << 16) | (impulse->num_lo << 0);

	impulse_archive.impulse[impulse_number % IMPULSE_ARCHIVE_SIZE] = *impulse;
}
