
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f429i_discovery.h"

int adc_convert(){
 ADC_SoftwareStartConv(ADC1);//Start the conversion
 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
 return ADC_GetConversionValue(ADC1); //Return the converted data
}

int ConvertedValue = 0;

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOA | RCC_AHB1ENR_GPIOCEN;//zet de GPIOG en GPIOA en de ADC aan

	//config de LEDS
	GPIOG->MODER |= 1<<(13*2) | 1<<(14*2);
	GPIOG->OSPEEDR = 0;
	GPIOG->OTYPER = 0;
	GPIOG->PUPDR = 0;

	RCC->APB2ENR |= RCC_APB2Periph_ADC1;//zet de APB2 clock aan omdat we deze gebruiken voor de ADC

	ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
	//ADC pin aan zetten
	GPIOC->MODER |= GPIO_Mode_AN<<(0*2);
	GPIOC->OSPEEDR = 0;
	GPIOC->OTYPER = 0;
	GPIOC->PUPDR = 0;
	//ADC structure configuration (begin niet aan de registers van de ADC deze zijn ultra moeilijk
	ADC_DeInit();
	ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
	ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit number giving a maximum value of 4096
	ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
	ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
	ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
	ADC_init_structure.ADC_NbrOfConversion = 1;//I think this one is clear :p
	ADC_init_structure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel
	ADC_Init(ADC1,&ADC_init_structure);//Initialize ADC with the previous configuration
	//Enable ADC conversion
	ADC_Cmd(ADC1,ENABLE);
	//Select the channel to be read from
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);
	while(1)
	{
		ConvertedValue = adc_convert();
	}
}
