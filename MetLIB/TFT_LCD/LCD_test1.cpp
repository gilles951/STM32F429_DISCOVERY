
#include "stm32f4xx.h"
#include "stm32f429i_discovery_lcd.h"

int main(void)
{
	LCD_Init();
	LCD_LayerInit();

	/* LTDC reload configuration */
	LTDC_ReloadConfig(LTDC_IMReload);

	/* Enable the LTDC */
	LTDC_Cmd(ENABLE);

	/* Set LCD foreground layer */
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	LCD_SetTransparency(0);

	/* Set LCD background layer */
	LCD_SetLayer(LCD_BACKGROUND_LAYER);

	/* LCD display message */
	LCD_Clear(LCD_COLOR_RED);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayStringLine(LCD_LINE_2,(uint8_t*)"     YOU'LL    ");
	LCD_DisplayStringLine(LCD_LINE_4,(uint8_t*)"     NEVER     ");
	LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)"      TAKE     ");
	LCD_DisplayStringLine(LCD_LINE_8,(uint8_t*)"       ME      ");
	LCD_DisplayStringLine(LCD_LINE_10,(uint8_t*)"     ALIVE     ");


	while(1)
	{

	}
}
