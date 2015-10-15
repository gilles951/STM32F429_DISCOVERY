/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
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


	// volatile int i;
    while (1) {
 //   	LCD_DisplayStringLine(LCD_LINE_10 , "Hello World");
   	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
    		GPIO_WriteBit(GPIOG,GPIO_Pin_13 | GPIO_Pin_14,Bit_SET);
    	} else {
    		GPIO_WriteBit(GPIOG,GPIO_Pin_13 | GPIO_Pin_14,Bit_RESET);
    	}

    //	for(;;);
    }
}
