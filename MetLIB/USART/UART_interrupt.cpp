
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

void rcc_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	// turn the clock on for register A
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 	// turn USART2 on
}

void GPIO_init(void){
	GPIO_InitTypeDef GPIO_InitDef;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;			// init pin 2 as TX and 3 as RX
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;					// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;						// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;					// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_2MHz;					// init 2 Mhz

	GPIO_Init(GPIOA, &GPIO_InitDef);						//Initialize pins

	 /* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);		// turn tx on
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);		// turn rx on
}

void USART2_init(void){
	USART_InitTypeDef USART_InitDef;

	USART_InitDef.USART_BaudRate = 115200;
	USART_InitDef.USART_WordLength = USART_WordLength_8b;
	USART_InitDef.USART_StopBits = USART_StopBits_1;
	USART_InitDef.USART_Parity = USART_Parity_No;
	USART_InitDef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_Init(USART2, &USART_InitDef);

	USART_Cmd(USART2, ENABLE);		
}

void USART2_init_interrupt(void){
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	NVIC_InitTypeDef NVIC_InitDef;				// Nested Vector Interrupt Controller

	NVIC_InitDef.NVIC_IRQChannel = USART2_IRQn;		 // we want to configure the USART2 interrupts
	NVIC_InitDef.NVIC_IRQChannelPreemptionPriority = 0;	 // this sets the priority group of the USART1 interrupts
	NVIC_InitDef.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitDef.NVIC_IRQChannelCmd = ENABLE;		 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitDef);				// the properties are passed to the NVIC_Init function which takes care of the low level stuff
}
			

	void USART_SendString(char *s){
	  while(*s) {
	    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
	    USART_SendData(USART2, *s++); // Send Char
	  }
	}

	char USART_ReceiveChar(void){
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		return USART_ReceiveData(USART2);
	}

	void USART2_IRQHandler(void) {
	    //Check if interrupt was because data is received
	    if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
	    	uint16_t value = USART_ReceiveChar();
	    	USART_SendString(&value);
	        //Clear interrupt flag
	        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	    }
	}

int main(void) {
	rcc_init();
	GPIO_init();
	USART2_init();
	USART2_init_interrupt();

   while (1) {
   	USART_SendString("Hello World!");
    }
}
