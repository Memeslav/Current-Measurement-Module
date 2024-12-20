#include "Current_handler.h"

void Current_handler_update(Current_handler_buffer_t *buffer, uint16_t signal)
{
	Counter_Update(&buffer->counter, signal);

    if (buffer->counter.quantity == 1)	{	buffer->maximal = signal;	buffer->minimal = signal;}

    else								{	buffer->minimal = (signal < buffer->minimal) ? signal : buffer->minimal;
        									buffer->maximal = (signal > buffer->maximal) ? signal : buffer->maximal;}
}
