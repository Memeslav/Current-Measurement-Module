#include "DRIVER_ADC.h"

ADC_STATE	adc_state	= DATA_READY;

struct adc_raw {ADC_Level_t data[ADC_CHANNELS];} adc_raw = {0};

static void DMA_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel1->CMAR		 = (uint32_t)(&adc_raw);
		DMA1_Channel1->CPAR		 = (uint32_t)(&(ADC1->DR));
		DMA1_Channel1->CNDTR	 = 	ADC_CHANNELS;
		DMA1_Channel1->CCR		|=	DMA_CCR_HTIE;
		DMA1_Channel1->CCR		|= 	DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
		DMA1_Channel1->CCR		|=	DMA_CCR_PL_Msk	| DMA_CCR_MINC;
		DMA1_Channel1->CCR		|= 	DMA_CCR_CIRC	| DMA_CCR_EN;

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
static void ADC_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

		ADC1->CFGR2 	|= ADC_CFGR2_CKMODE_Msk	| ADC_CFGR2_OVSR_Msk 	| ADC_CFGR2_OVSS_3 		| ADC_CFGR2_OVSE;
		ADC->CCR 		|= ADC_CCR_VREFEN 		| ADC_CCR_TSEN;
		ADC1->CR 	 	|= ADC_CR_ADVREGEN		| ADC_CR_ADCAL;
		while(ADC1->CR & ADC_CR_ADCAL);
		ADC1->CHSELR	|= ADC_CHSELR_CHSEL8 	| ADC_CHSELR_CHSEL9 	| ADC_CHSELR_CHSEL17 	| ADC_CHSELR_CHSEL18;
		ADC1->CFGR1 	|= ADC_CFGR1_AUTOFF 	| ADC_CFGR1_DMACFG 		| ADC_CFGR1_DMAEN;
		ADC1->IER 		|= ADC_IER_EOSIE;
		ADC1->CR 		|= ADC_CR_ADEN;
}

void Driver_ADC_Enable	(void)	{DMA_Init();	ADC_Init();}
void Driver_ADC_Measure	(void)
{
	if(adc_state == IN_PROCESS) {return;}
	adc_state = IN_PROCESS;
	ADC1->CR |= ADC_CR_ADSTART;
}

ADC_Level_t Driver_ADC_Get_Channel	(ADC_Channel channel)	{return adc_raw.data[channel];}
ADC_STATE 	Driver_ADC_Get_State	(void)					{return adc_state;}

void DMA1_Channel1_IRQHandler(void)
{
	if((DMA1->ISR & DMA_ISR_TCIF1) == DMA_ISR_TCIF1)
	{
		DMA1->IFCR |= DMA_IFCR_CHTIF1;
		adc_state = DATA_READY;
	}
	NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
}
