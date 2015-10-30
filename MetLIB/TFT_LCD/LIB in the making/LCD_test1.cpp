
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
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	LCD_SetTransparency(0);

	/* Set LCD background layer */
	LCD_SetLayer(LCD_BACKGROUND_LAYER);

	/* LCD display message */
	LCD_Clear(LCD_COLOR_WHITE);
	//LCD_Clear2(LCD_COLOR_BLUE);
	/*LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayStringLine(LCD_LINE_2,(uint8_t*)"     YOU'LL    ");
	LCD_DisplayStringLine(LCD_LINE_4,(uint8_t*)"     NEVER     ");
	LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)"      TAKE     ");
	LCD_DisplayStringLine(LCD_LINE_8,(uint8_t*)"       ME      ");
	LCD_DisplayStringLine(LCD_LINE_10,(uint8_t*)"     ALIVE     ");*/

	while(1)
	{
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i1 = RNG_GetRandomNumber()%240;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i2 = RNG_GetRandomNumber()%360;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i3 = RNG_GetRandomNumber()%400;
		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i4 = RNG_GetRandomNumber()%2;

		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		LCD_SetTextColor(RNG_GetRandomNumber());
		LCD_DrawLine(i1,i2,i3,i4);

		while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET);
		int i = RNG_GetRandomNumber()%100000;
		for(;i>0;i--);

		/*
			LCD_Clear(LCD_COLOR_RED);
			/*LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_DisplayStringLine(LCD_LINE_2,(uint8_t*)"     YOU'LL    ");
			LCD_DisplayStringLine(LCD_LINE_4,(uint8_t*)"     NEVER     ");
			LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)"      TAKE     ");
			LCD_DisplayStringLine(LCD_LINE_8,(uint8_t*)"       ME      ");
			LCD_DisplayStringLine(LCD_LINE_10,(uint8_t*)"     ALIVE     ");*//*
			i++;
		}
		else if(i==1)
		{
			LCD_Clear(LCD_COLOR_BLUE);
			i++;
		}
		else
		{
			LCD_Clear(LCD_COLOR_GREEN);
			i=0;
		}*/
	}
}
