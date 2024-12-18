#include <Impulse_archive.h>

volatile IMPULSE_ARCHIVE impulse_archive = {0};
uint16_t* impulses = (uint16_t*)&impulse_archive;

void Save_Impulse_to_Archive(IMPULSE* impulse)
{
	uint32_t impulse_number = Register_32b_Get(&impulse->num);

	impulse_archive.impulse[impulse_number % IMPULSE_ARCHIVE_SIZE] = *impulse;
}
