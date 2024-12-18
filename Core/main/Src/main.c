#include "main.h"

Register_32b_t boop = {0};
uint32_t meme = 0;

int main(void)
{
	meme = Register_32b_Get(&boop);

    while (1)
    {
    	Register_32b_Increment(&boop);
    	meme = Register_32b_Get(&boop);
    }
}
