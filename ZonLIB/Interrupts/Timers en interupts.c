
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f429i_discovery.h"


uint32_t temp = 0;

//Timer 2 interupt handler
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		//deel de timer tick door 1000000
		temp++;
		if(temp>1000000)
		{
			GPIOG->ODR ^= GPIO_Pin_14;//toggle pin 14
			temp = 0;
		}
	}
}

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOA;//zet de GPIOG en GPIOA aan
	RCC->APB1ENR |= RCC_APB1Periph_TIM2;//TIM2 aan

	//config de LEDS
	GPIOG->MODER |= 1<<(13*2) | 1<<(14*2);
	GPIOG->OSPEEDR = 0;
	GPIOG->OTYPER = 0;
	GPIOG->PUPDR = 0;

	//zet de ISR aan
	NVIC->IP[TIM2_IRQn] = 35;
	NVIC->ISER[TIM2_IRQn >> 0x05] = (uint32_t)0x01 << (TIM2_IRQn & (uint8_t)0x1F);

	//init de timer
	TIM2->CR1 = TIM_CR1_CEN;//start de timer
	TIM2->ARR = 500;
	TIM2->PSC = 40000;
	TIM2->EGR = TIM_PSCReloadMode_Immediate;

	//interrupt TIM2 aan
	TIM2->DIER |= TIM_IT_Update;

	while(1)
	{
	}
}
