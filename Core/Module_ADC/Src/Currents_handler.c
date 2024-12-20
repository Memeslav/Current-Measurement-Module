#include "Current_handler.h"

void Current_handler_update(Current_handler_buffer_t *buffer, uint16_t signal)
{
	Average_handler_update(&buffer->counter, signal);

    if (buffer->counter.number_of_measurements == 1)	{	buffer->maximal = signal;	buffer->minimal = signal;}

    else												{	buffer->minimal = (signal < buffer->minimal) ? signal : buffer->minimal;
        													buffer->maximal = (signal > buffer->maximal) ? signal : buffer->maximal;}
}
