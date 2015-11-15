
#include "stm32f4xx.h"//basis functies
#include "stm32f429i_discovery_lcd.h"//het bordje
#include "LIB_LCDTFT.h"//LCDTFT lib

#include "stm32f429i_discovery_lcd.h"

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

	/*zet de kleur van de tekst en de kleur van de achtergrond van de tekst*/
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetBackColor(LCD_COLOR_WHITE);

	/*Zet het font op 16x24*/
	LCD_SetFont(&Font16x24);

	/*zet tekst op het scherm*/
	LCD_DisplayStringLine(LCD_LINE_3, (uint8_t*)(" Er staat tekst"));
	LCD_DisplayStringLine(LCD_LINE_5, (uint8_t*)(" op het scherm"));
	LCD_DisplayStringLine(LCD_LINE_7, (uint8_t*)("    GEWELDIG"));

	while(1){}
}
