#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); // 
	GPIO_InitTypeDef GPIO_InitDef;

GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14; // we gaan pin 13 en 14 gebruiken

	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;		// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 		// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;	// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;	// init 100 MHZ

	//Initialize pins
	GPIO_Init(GPIOG, &GPIO_InitDef);

	volatile int i;
    while (1) {
    	// Toggle leds
    	GPIO_ToggleBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);
    	// Waste some tome
    	for (i = 0; i < 500000; i++);
    }
}