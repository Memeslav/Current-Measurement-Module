#include "Current_handler.h"

void Current_handler_update(Current_handler_buffer_t *buffer, uint16_t signal)
{
    buffer->number_of_measurements++;
    buffer->sum_of_all_measurements += signal;

    if (buffer->number_of_measurements == 1)	{	buffer->maximal = signal;	buffer->minimal = signal;}

    else										{	buffer->minimal = (signal < buffer->minimal) ? signal : buffer->minimal;
        											buffer->maximal = (signal > buffer->maximal) ? signal : buffer->maximal;}
}
