#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
			

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); // turns the clock on for register G
	GPIO_InitTypeDef GPIO_InitDef;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13;	// init pin 13 for use
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

	//Initialize pins
	GPIO_Init(GPIOG, &GPIO_InitDef);

	volatile int i;
    while (1) {

    	// turn led on
     GPIO_WriteBit(GPIOG,GPIO_Pin_13,Bit_SET);
    	// Waste some tome
    	for (i = 0; i < 5000000; i++);

    	// turn led off
    GPIO_WriteBit(GPIOG,GPIO_Pin_13,Bit_RESET);

    // Waste some tome
        for (i = 0; i < 5000000; i++);
    }
}