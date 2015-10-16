
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f429i_discovery.h"

/*Smal delay lib*/
uint32_t multiplier;
void TM_Delay_Init(void) {
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);
    multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}

void TM_DelayMicros(uint32_t micros) {
    micros = micros * multiplier - 10;
    while (micros--);
}

void TM_DelayMillis(uint32_t millis) {
    millis = 1000 * millis * multiplier - 10;
    while (millis--);
}
/***************/

int main(void)
{
	TM_Delay_Init();//init delay

	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOA;//zet de GPIOG en GPIOA aan

	//zet de pinnen 13 en 14 van GPIOG aan als uitgang op lage snelheid zonder pull weerstanden
	GPIOG->MODER |= 1<<(13*2) | 1<<(14*2);
	GPIOG->OSPEEDR = 0;
	GPIOG->OTYPER = 0;
	GPIOG->PUPDR = 0;

	while(1)
	{
		//lees GPIOA in en zet er een masker over
		if(GPIOA->IDR & GPIO_Pin_0)
		{
			//toggle de leds
			GPIOG->ODR ^= GPIO_Pin_14;
			GPIOG->ODR ^= GPIO_Pin_13;
			TM_DelayMillis(200);//wacht 200 ms
		}
		else
		{
			//set een led en reset de andere
			GPIOG->BSRRL = GPIO_Pin_13;
			GPIOG->BSRRH = GPIO_Pin_14;
		}
	}
}
