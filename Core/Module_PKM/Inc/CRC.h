#ifndef CRC_H_
#define CRC_H_

#include "stm32l053xx.h"

void 					CRC_Enable		(void);
static inline void 		CRC_Reset		(void)			{CRC->CR |= CRC_CR_RESET;}
static inline void 		CRC_Load		(uint16_t data)	{*((__IO uint16_t *)&CRC->DR) = data;}
static inline uint16_t	CRC_Get_Result	(void)			{return CRC->DR;}

#endif
