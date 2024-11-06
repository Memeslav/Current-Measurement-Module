#include "LSI.h"

LSI_STATUS LSI_Enable(void)
{
    uint32_t timeout = LSI_LAUNCH_TIMEOUT;

    RCC->CSR |= RCC_CSR_LSION;
    while (!(RCC->CSR & RCC_CSR_LSIRDY) && timeout--){}

    return (RCC->CSR & RCC_CSR_LSIRDY) ? lsi_enabled : lsi_failure;
}
