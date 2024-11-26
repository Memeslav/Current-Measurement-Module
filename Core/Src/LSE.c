#include "LSE.h"

bool LSE_Enable(void)
{
    uint32_t timeout = LSE_LAUNCH_TIMEOUT;

	Disable_Backup_Write_Protection();
		RCC->CSR |=	 RCC_CSR_LSEON;
		while(!(RCC->CSR & RCC_CSR_LSERDY) && timeout--){}
	Enable_Backup_Write_Protection();

    if (RCC->CSR & RCC_CSR_LSERDY) 	{return true;}
    else 							{return false;}
}
