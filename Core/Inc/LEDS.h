#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "stm32l053xx.h"

void LED_Init(void);
uint8_t LED_Check_Jumper(void);

void LED_RED_ON (void);
void LED_RED_OFF(void);
void LED_RED_TOGGLE(void);

void LED_BLU_ON (void);
void LED_BLU_OFF(void);
void LED_BLU_TOGGLE(void);

void LED_YEL_ON (void);
void LED_YEL_OFF(void);
void LED_YEL_TOGGLE(void);

void LED_GRN_ON (void);
void LED_GRN_OFF(void);
void LED_GRN_TOGGLE(void);

#endif
