/*
 * LIB_LCDTFT.h
 *
 *  Created on: 27-okt.-2015
 *      Author: gybel_000
 */

#ifndef LIB_LCDTFT_H_
#define LIB_LCDTFT_H_

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_sdram.h"
#include "LIB_LCDTFTConf.h"

#include "image565.h"

class LCDTFT: public LCDTFTConf
{
	public:
		LCDTFT();
		void LCD_Clear(uint16_t);
		void LCD_DrawDot(int, int, uint16_t);
		void LCD_DrawStraigtLine(int, int, int, uint8_t, uint16_t);
		void LCD_DrawLine(int, int, int, int, uint16_t);
		void LCD_DrawBMP(uint32_t);

	protected:

	private:
};

#endif /* LIB_LCDTFT_H_ */
