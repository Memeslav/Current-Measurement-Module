#include "UNIXTIME.h"

void Unixtime_Increment(volatile UNIXTIME* unixtime)
{
    unixtime->lo += 1;

    if (unixtime->lo == 0)
    {
        unixtime->hi += 1;
    }
}
