#ifndef FILTER_H_
#define FILTER_H_

#include "Unixtime.h"

typedef enum	{	DENIED 		= 0,
					APPROVED 	= 1,	}	FILTER_STATE;

typedef struct	{	Unixtime_t duration;	}	Filter_t;

static inline void Fliter_Clear (Filter_t* filter) 							{  *filter = (Filter_t){0};}
static inline void Filter_Set	(Filter_t* filter, Unixtime_t duration) 	{	filter->duration = duration;}

static inline FILTER_STATE Filter_Check	(	const Filter_t* filter,
											Unixtime_t current_duration)	{	return (current_duration >= filter->duration) ? APPROVED : DENIED;}

#endif
