/*
 * Standaardstm32F4.cpp
 *
 *  Created on: 4-dec.-2015
 *      Author: Gebruiker
 */

#include "Standaardstm32F4.h"
#include <iostream>
#include <string>

uint16_t GPIO::Convert_Pin_X(int Pinnummer)
{
	uint16_t Pin_X_ ;
	switch(Pinnummer)
					{

					   case 0:
						   Pin_X_ = GPIO_Pin_0;
					   break;

					   case 1:
						   Pin_X_ = GPIO_Pin_1;
					   	break;

					   case 2:
						   Pin_X_ = GPIO_Pin_2;
					  	break;

					   case 3:
						   Pin_X_ = GPIO_Pin_3;
						break;

					   case 4:
						   Pin_X_ = GPIO_Pin_4;
					   	break;

					   case 5:
						   Pin_X_ = GPIO_Pin_5;
					  	break;

					   case 6:
						   Pin_X_ = GPIO_Pin_6;
					   	break;

					   case 7:
						   Pin_X_ = GPIO_Pin_7;
					  	break;
					   case 8:
						   Pin_X_ = GPIO_Pin_8;
					   break;

					   case 9:
						   Pin_X_ = GPIO_Pin_9;
					  break;

					   case 10:
						   Pin_X_ = GPIO_Pin_10;
					  break;

					   case 11:
						   Pin_X_ = GPIO_Pin_11;
					  break;

					   case 12:
						   Pin_X_ = GPIO_Pin_12;
					   break;

					   case 13:
						   Pin_X_ = GPIO_Pin_13;
					   break;

					   case 14:
						   Pin_X_ = GPIO_Pin_14;
					   break;

					   case 15:
						   Pin_X_ = GPIO_Pin_15;
					   break;
	/*
					   case "all":
						   Gekozen_pin = GPIO_Pin_All;
					   break;
					   */
					   default:

						   break;

					}
	 return Pin_X_;
}
uint32_t GPIO::Convert_Prescale_gate(char nummer_)
{
uint32_t Prescale_gate_ ;
switch (nummer_)
		{
		   case  'A':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOA;
		   break;

		   case 'B':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOB;
		   	break;

		   case 'C':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOC;

		  	break;

		   case 'D':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOD;

			break;

		   case 'E':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOE;

		   	break;

		   case 'F':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOF;

		  	break;

		   case 'G':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOG;

		   	break;

		   case 'H':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOH;

		  	break;
		   case 'I':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOI;

		   break;

		   case 'J':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOJ;

		  break;

		   case 'K':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOK;

		  break;
		   default:

			   break;
		}
		return Prescale_gate_;
	}

GPIO_TypeDef* GPIO::Convert_Port_x(char nummer__)
{
	GPIO_TypeDef* Port_x_ ;
	switch (nummer__)
		{
		   case  'A':
			   Port_x_ = GPIOA ;
		   break;

		   case 'B':
			   Port_x_ = GPIOB ;
		   	break;

		   case 'C':
			   Port_x_ = GPIOC ;

		  	break;

		   case 'D':
			   Port_x_ = GPIOD ;

			break;

		   case 'E':
			   Port_x_ = GPIOE ;

		   	break;

		   case 'F':
			   Port_x_ = GPIOF ;

		  	break;

		   case 'G':
			   Port_x_ = GPIOG ;

		   	break;

		   case 'H':
			   Port_x_ = GPIOH ;

		  	break;
		   case 'I':
			   Port_x_ = GPIOI ;

		   break;

		   case 'J':
			   Port_x_ = GPIOJ ;

		  break;

		   case 'K':
			   Port_x_ = GPIOK ;

		  break;
		   default:

			   break;
		}
		return Port_x_;
	}

GPIO::GPIO(char Poortnummer , int Pinnummer) {

	// uint32_t RCC_AHB1Periph ;

	Prescale_gate = Convert_Prescale_gate(Poortnummer);
	Port_x = Convert_Port_x(Poortnummer);
	Pin_X = Convert_Pin_X(Pinnummer);


	    RCC_AHB1PeriphClockCmd(Prescale_gate, ENABLE); // turns the clock on for register x
		GPIO_InitTypeDef GPIO_InitDef;

		GPIO_InitDef.GPIO_Pin = Pin_X;				// De gekozen pin wordt ingesteld.
		GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
		GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
		GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
		GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

		//Initialize pins
		GPIO_Init(Port_x, &GPIO_InitDef);
}
void GPIO::OType(GPIOOType_TypeDef otype)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_InitDef.GPIO_OType = otype;
	GPIO_Init(Port_x, &GPIO_InitDef);
}

void GPIO::Mode(GPIOMode_TypeDef  Mode)
		{
		GPIO_InitTypeDef GPIO_InitDef;
		GPIO_InitDef.GPIO_Mode = Mode;
		GPIO_Init(Port_x, &GPIO_InitDef);
		}

void GPIO::Speed(GPIOSpeed_TypeDef  Speed)
		{
		GPIO_InitTypeDef GPIO_InitDef;
		GPIO_InitDef.GPIO_Speed = Speed;
		GPIO_Init(Port_x, &GPIO_InitDef);
		}

void GPIO::PuPd(GPIOPuPd_TypeDef  PuPd)
		{
		GPIO_InitTypeDef GPIO_InitDef;
		GPIO_InitDef.GPIO_PuPd = PuPd;
		GPIO_Init(Port_x, &GPIO_InitDef);
		}
void GPIO::WriteBit(bool waarde)
		{
	BitAction Toestand;
	if (waarde == false)
	  {
		Toestand = Bit_RESET ;
	  }
	  else
	  {
		  Toestand = Bit_SET ;
	  }


	 	 	 	 GPIO_WriteBit(Port_x,Pin_X,Toestand);
		}

void Writeport(char Poortnummer , uint16_t value)
{
	uint32_t Prescale_gate_ ;
	GPIO_TypeDef* Port_x_ ;
	switch (Poortnummer)
			{

			   case  'A':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOA;
				   Port_x_ = GPIOA ;
			   break;

			   case 'B':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOB;
				   Port_x_ = GPIOB ;
			   	break;

			   case 'C':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOC;
				   Port_x_ = GPIOC ;

			  	break;

			   case 'D':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOD;
				   Port_x_ = GPIOD ;

				break;

			   case 'E':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOE;
				   Port_x_ = GPIOE ;
			   	break;

			   case 'F':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOF;
				   Port_x_ = GPIOE ;
			  	break;

			   case 'G':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOG;
				   Port_x_ = GPIOG ;
			   	break;

			   case 'H':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOH;
				   Port_x_ = GPIOH ;
			  	break;
			   case 'I':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOI;
				   Port_x_ = GPIOI ;
			   break;

			   case 'J':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOJ;
				   Port_x_ = GPIOJ ;
			  break;

			   case 'K':
				   Prescale_gate_ = RCC_AHB1Periph_GPIOK;
				   Port_x_ = GPIOJ ;
			  break;
			   default:

				   break;
			}


	        			RCC_AHB1PeriphClockCmd(Prescale_gate_, ENABLE); // turns the clock on for register x
				 		GPIO_InitTypeDef GPIO_InitDef;

				 		GPIO_InitDef.GPIO_Pin = GPIO_Pin_All;				// De gekozen pin wordt ingesteld.
				 		GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
				 		GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
				 		GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
				 		GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

				 		//Initialize pins
				 		GPIO_Init(Port_x_, &GPIO_InitDef);
				 		GPIO_Write(Port_x_,value);
		}








GPIO::~GPIO() {
	// TODO Auto-generated destructor stub
}

GPIO_Gate::~GPIO_Gate() {
	// TODO Auto-generated destructor stub
}

uint32_t GPIO_Gate::Convert_Prescale_gate(char nummer_)
{
uint32_t Prescale_gate_ ;
switch (nummer_)
		{
		   case  'A':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOA;
		   break;

		   case 'B':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOB;
		   	break;

		   case 'C':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOC;

		  	break;

		   case 'D':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOD;

			break;

		   case 'E':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOE;

		   	break;

		   case 'F':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOF;

		  	break;

		   case 'G':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOG;

		   	break;

		   case 'H':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOH;

		  	break;
		   case 'I':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOI;

		   break;

		   case 'J':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOJ;

		  break;

		   case 'K':
			   Prescale_gate_ = RCC_AHB1Periph_GPIOK;

		  break;
		   default:

			   break;
		}
		return Prescale_gate_;
	}

GPIO_TypeDef* GPIO_Gate::Convert_Port_x(char nummer__)
{
	GPIO_TypeDef* Port_x_ ;
	switch (nummer__)
		{
		   case  'A':
			   Port_x_ = GPIOA ;
		   break;

		   case 'B':
			   Port_x_ = GPIOB ;
		   	break;

		   case 'C':
			   Port_x_ = GPIOC ;

		  	break;

		   case 'D':
			   Port_x_ = GPIOD ;

			break;

		   case 'E':
			   Port_x_ = GPIOE ;

		   	break;

		   case 'F':
			   Port_x_ = GPIOF ;

		  	break;

		   case 'G':
			   Port_x_ = GPIOG ;

		   	break;

		   case 'H':
			   Port_x_ = GPIOH ;

		  	break;
		   case 'I':
			   Port_x_ = GPIOI ;

		   break;

		   case 'J':
			   Port_x_ = GPIOJ ;

		  break;

		   case 'K':
			   Port_x_ = GPIOK ;

		  break;
		   default:

			   break;
		}
		return Port_x_;
	}

GPIO_Gate::GPIO_Gate(char Poortnummer , uint16_t value)
{
	Prescale_gate = Convert_Prescale_gate(Poortnummer);
	Port_x = Convert_Port_x(Poortnummer);


	RCC_AHB1PeriphClockCmd(Prescale_gate, ENABLE); // turns the clock on for register x
	GPIO_InitTypeDef GPIO_InitDef;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_All;				// De gekozen pin wordt ingesteld.
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

	//Initialize pins
	GPIO_Init(Port_x, &GPIO_InitDef);
	GPIO_Write(Port_x,value);
}

void GPIO_Gate::Writeport(uint16_t value)
{
	GPIO_Write(Port_x,value);
}


USART::USART(void)
{
	// RCC_inite
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	// turn the clock on for register A
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 	// turn USART2 on

	// GPIO_inite
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

		// usart2_inite

		USART_InitTypeDef USART_InitDef;

			USART_InitDef.USART_BaudRate = 115200;
			USART_InitDef.USART_WordLength = USART_WordLength_8b;
			USART_InitDef.USART_StopBits = USART_StopBits_1;
			USART_InitDef.USART_Parity = USART_Parity_No;
			USART_InitDef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
			USART_InitDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

			USART_Init(USART2, &USART_InitDef);

			USART_Cmd(USART2, ENABLE);

			// USART2_init_interrupt
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

		    NVIC_InitTypeDef NVIC_InitDef;				// Nested Vector Interrupt Controller

		    NVIC_InitDef.NVIC_IRQChannel = USART2_IRQn;		 // we want to configure the USART2 interrupts
			NVIC_InitDef.NVIC_IRQChannelPreemptionPriority = 0;	 // this sets the priority group of the USART1 interrupts
			NVIC_InitDef.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
			NVIC_InitDef.NVIC_IRQChannelCmd = ENABLE;		 // the USART1 interrupts are globally enabled
			NVIC_Init(&NVIC_InitDef);				// the properties are passed to the NVIC_Init function which takes care of


}

void USART::sent(char *s)
{
	 while(*s) {
		    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		    USART_SendData(USART2, *s++); // Send Char
		  }

}

char USART::Receive(void)
{
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			return USART_ReceiveData(USART2);
}

// deze moet nog in het hoofd programma toegevoegd worden.

/*

void USART2_IRQHandler(void) {
	    //Check if interrupt was because data is received
	    if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
	    	uint16_t value = USART_ReceiveChar();
	    	USART_SendString(&value);
	        //Clear interrupt flag
	        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	    }
	}
	*/


