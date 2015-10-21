#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
			
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

	GPIO_Init(GPIOA, &GPIO_InitDef);							//Initialize pins

	 /* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
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


int main(void) {

	rcc_init();
	GPIO_init();
	USART2_init();

	USART_SendString("Hello World\n");
    while (1) {
    	if (USART_ReceiveChar() == 'g'){
    		USART_SendString("Received your message\r\n");
    	}
    }
}