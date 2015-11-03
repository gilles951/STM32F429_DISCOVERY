
#include "stm32f4xx.h"
#include "stm32f429i_discovery_lcd.h"
#include "LIB_LCDTFT.h"

void RNG_Config(void)
{
	/* Enable RNG clock source */
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);

	/* RNG Peripheral enable */
	RNG_Cmd(ENABLE);
}


int main(void)
{
	RNG_Config();

	LCDTFT lcd = LCDTFT();

	/* Set LCD foreground layer */
	lcd.LCD_SetLayer(LCD_FOREGROUND_LAYER);
	lcd.LCD_SetTransparency(0);

	/* Set LCD background layer */
	lcd.LCD_SetLayer(LCD_BACKGROUND_LAYER);
	lcd.LCD_Clear(LCD_COLOR_WHITE);

	int j = 0;

	while(1)
	{
		j++;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i1 = RNG_GetRandomNumber()%240;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i2 = RNG_GetRandomNumber()%360;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i3 = RNG_GetRandomNumber()%100;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i4 = RNG_GetRandomNumber()%2;

		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		//LCD_SetTextColor(RNG_GetRandomNumber());
		lcd.LCD_DrawStraigtLine(i1, i2, i3, i4, RNG_GetRandomNumber());

		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i = RNG_GetRandomNumber()%1000000;
		for(;i>0;i--);
		if(j>1000)
			while(1);
	}
}
