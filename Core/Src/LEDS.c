#include "LEDS.h"

typedef enum
{
	off		= 0,
	on		= 1,
}
LED_STATUS;


uint8_t led_status[4] = {0};


void LED_Enable(LED_COLOUR led_colour)
{
	switch(led_colour)
	{
		case RED:

			RCC->IOPENR  |=   RCC_IOPENR_GPIOAEN;
				GPIOA->MODER &= ~(GPIO_MODER_MODE15_Msk);
				GPIOA->MODER |=   GPIO_MODER_MODE15_0;
				GPIOA->BSRR  |=   GPIO_BSRR_BS_15;
				led_status[RED] = on;
				break;

		case BLU:

			RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;
				GPIOB->MODER &= ~(GPIO_MODER_MODE3_Msk);
				GPIOB->MODER |=   GPIO_MODER_MODE3_0;
				GPIOB->BSRR  |=   GPIO_BSRR_BS_3;
				led_status[BLU] = on;
				break;

		case YEL:

			RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;
				GPIOB->MODER &= ~(GPIO_MODER_MODE4_Msk);
				GPIOB->MODER |=   GPIO_MODER_MODE4_0;
				GPIOB->BSRR  |=   GPIO_BSRR_BS_4;
				led_status[YEL] = on;
				break;

		case GRN:

			RCC->IOPENR  |=   RCC_IOPENR_GPIOBEN;
				GPIOB->MODER &= ~(GPIO_MODER_MODE5_Msk);
				GPIOB->MODER |=   GPIO_MODER_MODE5_0;
				GPIOB->BSRR  |=   GPIO_BSRR_BS_5;
				led_status[GRN] = on;
				break;
	}
}

void LED_Disable(LED_COLOUR led_colour)
{
	switch(led_colour)
	{
		case RED:

			GPIOA->BSRR  |=   GPIO_BSRR_BR_15;
			led_status[RED] = off;
			break;

		case BLU:

			GPIOB->BSRR  |=   GPIO_BSRR_BR_3;
			led_status[BLU] = off;
			break;

		case YEL:

			GPIOB->BSRR  |=   GPIO_BSRR_BR_4;
			led_status[YEL] = off;
			break;

		case GRN:

			GPIOB->BSRR  |=   GPIO_BSRR_BR_5;
			led_status[GRN] = off;
			break;
	}
}

void LED_Toggle(LED_COLOUR led_colour)
{
	switch(led_colour)
	{
		case RED:

			if(led_status[RED] == on){LED_Disable(led_colour);}
			else {{LED_Enable(led_colour);}}
			break;

		case BLU:

			if(led_status[BLU] == on){LED_Disable(led_colour);}
			else {{LED_Enable(led_colour);}}
			break;

		case YEL:

			if(led_status[YEL] == on){LED_Disable(led_colour);}
			else {{LED_Enable(led_colour);}}
			break;

		case GRN:

			if(led_status[GRN] == on){LED_Disable(led_colour);}
			else {{LED_Enable(led_colour);}}
			break;
	}
}
