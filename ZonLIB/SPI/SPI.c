/*
 * SPI.c
 *
 *  Created on: 15-okt.-2015
 *      Author: gybel_000
 */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f429i_discovery.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOA;//zet de GPIOA aan

	//SPI pins (SPI1)
	GPIOA->MODER |= 2<<(5 * 2) | 2<<(6 * 2) | 2<<(7 * 2);

	//zet de IO pinnen op de juiste AF
	GPIOA->AFR[0] = GPIO_AF_SPI1<<(5 * 4) | GPIO_AF_SPI1<<(6 * 4) | GPIO_AF_SPI1<<(7 * 4);

	//zet de SPI clock aan
	RCC->APB2ENR |= RCC_APB2Periph_SPI1;

	//configure SPI1
	SPI1->CR1 &= 0x3040;//verwijder alle vorige functionaliteit
	SPI1->CR1 |= SPI_BaudRatePrescaler_256 | SPI_Mode_Master | SPI_NSS_Soft | SPI_NSSInternalSoft_Set;//zet de nieuwe functionaliteit
	SPI1->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SMOD);//zet I2S af
	SPI1->CRCPR = 0;

	SPI1->CR1 |= SPI_CR1_SPE; // enable SPI1

	while(1)
	{
		SPI1->DR = 0x8a; // write data to be transmitted to the SPI data register
		while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
		while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
		while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	}
}
