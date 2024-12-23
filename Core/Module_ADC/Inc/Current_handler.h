#ifndef CURRENTS_HANDLER_H_
#define CURRENTS_HANDLER_H_

#include "Counter.h"

typedef struct	{	Counter_t counter;
					uint16_t maximal;
					uint16_t minimal;	}	 Current_handler_t;

void 				Current_Handler_Update	(Current_handler_t *buffer, uint16_t signal);
static inline void 	Current_Handler_Clear	(Current_handler_t *buffer)						{*buffer = (Current_handler_t){0};}

static inline uint16_t Current_Handler_Get_Maximal(const Current_handler_t *buffer)			{return buffer->maximal;}
static inline uint16_t Current_Handler_Get_Minimal(const Current_handler_t *buffer)			{return buffer->minimal;}
static inline uint16_t Current_Handler_Get_Average(const Current_handler_t *buffer)			{return Counter_Get_Average(&buffer->counter);}

#endif
