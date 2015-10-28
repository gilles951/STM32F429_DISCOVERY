/**
  ******************************************************************************
  * @file    flankdetectie
  * @author  Michiel Pieters
  * @version V1.0
  * @date    10-December-2015
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f429i_discovery_lcd.h"
			

int main(void) {

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); // turns the clock on for register G
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // turns the clock on for register A
	GPIO_InitTypeDef GPIO_InitDef;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	// init pin 13 for use
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

	//Initialize pins
	GPIO_Init(GPIOG, &GPIO_InitDef);

	GPIO_InitDef.GPIO_Pin =  GPIO_Pin_0;				// init pin 13 for use
	GPIO_InitDef.GPIO_OType = GPIO_OType_OD;			// init open drain
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;				// init input
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz


	//Initialize pins
	GPIO_Init(GPIOA, &GPIO_InitDef);


	int old; // Declareer de variabelen old.
	int i ;  //Declareer de variabelen i.
	int nu;  //Declareer de variabelen nu.
	old = 0 ; // Bij het opstarten is de drukknop nog niet ingedrukt geweest.

    while (1) {
   	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) && (old == 0)){ // Hebben we een positieve flank?
   		GPIO_ToggleBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14); // Troggel dan de 2 led’s.

    		old = 1 ; // Geef aan dat er een positieve flank is geweest.
    	}
      nu = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0); // deze code dient enkel om het programma te testen in debug mode.

	if (!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)) && (old == 1)){ // Voer het volgende uit bij een negatieve flank.
    		old = 0 ; // Geef aan dat er een negatieve flank is geweest.
    		for (i = 0; i < 5000000; i++); // Wacht een tijd om de invloed van contact dender te vermeiden.
    	}
    }
}

