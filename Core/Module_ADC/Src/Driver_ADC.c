#include "Driver_ADC.h"

static ADC_State_e state;
static ADC_Level_t channels[ADC_CHANNELS];

static void DMA_Enable(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel1->CMAR		 = (uint32_t)(&channels);
		DMA1_Channel1->CPAR		 = (uint32_t)(&(ADC1->DR));
		DMA1_Channel1->CNDTR	 = 	ADC_CHANNELS;
		DMA1_Channel1->CCR		|=	DMA_CCR_HTIE;
		DMA1_Channel1->CCR		|= 	DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
		DMA1_Channel1->CCR		|=	DMA_CCR_PL_Msk	| DMA_CCR_MINC;
		DMA1_Channel1->CCR		|= 	DMA_CCR_CIRC	| DMA_CCR_EN;

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

static void ADC_Enable(void)
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

static ADC_State_e Get_State 	(void) 					{return state;}
static ADC_Level_t Get_Channel	(ADC_Channel_e channel)	{return channels[channel];}
static void Get_All_Channels 	(ADC_Level_t *data) 	{for (int i = 0; i < ADC_CHANNELS; i++) {data[i] = channels[i];}}

static void Measure				(void)
{
	if(state == Measure_in_Progress) {return;}
	state = Measure_in_Progress;
	ADC1->CR |= ADC_CR_ADSTART;
}

void ADC_Init(ADC_t *adc)
{
	DMA_Enable();
	ADC_Enable();

	adc->state 		= &state;
	adc->channels 	= channels;

	for(int i = 0; i < ADC_CHANNELS; i++){channels[i] = 0;}

	adc->measure 			= Measure;
	adc->get_state 			= Get_State;
	adc->get_channel		= Get_Channel;
	adc->get_all_channels	= Get_All_Channels;
}
