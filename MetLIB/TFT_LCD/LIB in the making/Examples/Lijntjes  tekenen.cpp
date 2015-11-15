
#include "stm32f4xx.h"//basis functies
#include "stm32f429i_discovery_lcd.h"//het bordje
#include "LIB_LCDTFT.h"//LCDTFT lib

int main(void)
{
	/*Maak het LCD object aan (initialiseer het LCD)*/
	LCDTFT lcd = LCDTFT();

	/*zet de voorste laag af door deze transparant te maken*/
	lcd.LCD_SetLayer(LCD_FOREGROUND_LAYER);
	lcd.LCD_SetTransparency(0);

	/*maak de achterste laag wit door deze te clearen*/
	lcd.LCD_SetLayer(LCD_BACKGROUND_LAYER);
	lcd.LCD_Clear(LCD_COLOR_WHITE);

	/*teken de lijn*/
	lcd.LCD_DrawLine(50, 50, 200, 100, LCD_COLOR_RED);

	while(1){}
}
