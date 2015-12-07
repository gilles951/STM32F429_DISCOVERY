/*
 * Standaardstm32F4.h
 *
 *  Created on: 4-dec.-2015
 *      Author: Gebruiker
 */

#ifndef STANDAARDSTM32F4_H_
#define STANDAARDSTM32F4_H_

#include "stm32f4xx_conf.h"

class GPIO {
public:

	uint32_t Prescale_gate ;
	GPIO_TypeDef* Port_x ;
	uint16_t Pin_X ;
	GPIO(char Poortnummer , int Pinnummer);
	void WriteBit(bool waarde);
	void OType(GPIOOType_TypeDef  otype);
	void Mode(GPIOMode_TypeDef  Mode);
	void PuPd(GPIOPuPd_TypeDef  PuPd);
	void Speed(GPIOSpeed_TypeDef  Speed);
	virtual ~GPIO();
private:
	uint32_t Convert_Prescale_gate(char nummer_);
	GPIO_TypeDef* Convert_Port_x(char nummer__);
	uint16_t Convert_Pin_X(int Pinnummer);
};

void Writeport(char Poortnummer , uint16_t value);

class GPIO_Gate{
public:

	uint32_t Prescale_gate ;
	GPIO_TypeDef* Port_x ;
	GPIO_Gate(char Poortnummer , uint16_t value);
	void Writeport(uint16_t value);
	virtual ~GPIO_Gate();
private:
	uint32_t Convert_Prescale_gate(char nummer_);
	GPIO_TypeDef* Convert_Port_x(char nummer__);
};

class USART{
public:
	USART(void);
	void sent(char *s);
	char  Receive(void);
	//void USART2_IRQHandler(void);
	virtual ~USART();
private:
	uint32_t Convert_Prescale_gate(char nummer_);
	GPIO_TypeDef* Convert_Port_x(char nummer__);
};

#endif /* STANDAARDSTM32F4_H_ */

