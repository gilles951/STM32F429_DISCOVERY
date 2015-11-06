/*
 * LIB_LCDTFT.cpp
 *
 *  Created on: 27-okt.-2015
 *      Author: gybel_000
 */

#include "LIB_LCDTFT.h"

uint32_t draws;

LCDTFT::LCDTFT()
{
	draws=0;
}

void LCDTFT::LCD_Clear(uint16_t Color)
{
  uint32_t index = 0;

  /* erase memory */
  for (index = 0x00; index < BUFFER_OFFSET; index++)
  {
    *(__IO uint16_t*)(CurrentFrameBuffer + (2*index)) = Color;
  }
}

void LCDTFT::LCD_DrawDot(int x, int y, uint16_t Color)
{
	while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET && draws !=0);

	DMA2D_InitTypeDef      DMA2D_InitStruct;
	uint32_t  Xaddress = CurrentFrameBuffer + 2*(LCD_PIXEL_WIDTH*y +x);

	DMA2D_DeInit();
	DMA2D_InitStruct.DMA2D_Mode = DMA2D_R2M;
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_RGB565;
	DMA2D_InitStruct.DMA2D_OutputGreen = (0x07E0 & Color) >> 5;
	DMA2D_InitStruct.DMA2D_OutputBlue = 0x001F & Color;
	DMA2D_InitStruct.DMA2D_OutputRed = (0xF800 & Color) >> 11;
	DMA2D_InitStruct.DMA2D_OutputAlpha = 0x0F;
	DMA2D_InitStruct.DMA2D_OutputMemoryAdd = Xaddress;

	DMA2D_InitStruct.DMA2D_OutputOffset = 0;
	DMA2D_InitStruct.DMA2D_NumberOfLine = 1;
	DMA2D_InitStruct.DMA2D_PixelPerLine = 1;

	DMA2D_Init(&DMA2D_InitStruct);
	DMA2D_StartTransfer();
	draws=1;
}

void LCDTFT::LCD_DrawStraigtLine(int x, int y, int length, uint8_t Direction, uint16_t Color)
{
	while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET && draws !=0);
	DMA2D_InitTypeDef      DMA2D_InitStruct;

	uint32_t  Xaddress = CurrentFrameBuffer + 2*(LCD_PIXEL_WIDTH*y + x);

	DMA2D_DeInit();
	DMA2D_InitStruct.DMA2D_Mode = DMA2D_R2M;
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_RGB565;
	DMA2D_InitStruct.DMA2D_OutputGreen = (0x07E0 & Color) >> 5;
	DMA2D_InitStruct.DMA2D_OutputBlue = 0x001F & Color;
	DMA2D_InitStruct.DMA2D_OutputRed = (0xF800 & Color) >> 11;
	DMA2D_InitStruct.DMA2D_OutputAlpha = 0x0F;
	DMA2D_InitStruct.DMA2D_OutputMemoryAdd = Xaddress;

	if(Direction == LCD_DIR_HORIZONTAL)
	{
		DMA2D_InitStruct.DMA2D_OutputOffset = 0;
		DMA2D_InitStruct.DMA2D_NumberOfLine = 1;
	    DMA2D_InitStruct.DMA2D_PixelPerLine = length;
	}
	else
	{
		DMA2D_InitStruct.DMA2D_OutputOffset = LCD_PIXEL_WIDTH - 1;
	    DMA2D_InitStruct.DMA2D_NumberOfLine = length;
	    DMA2D_InitStruct.DMA2D_PixelPerLine = 1;
	}
	DMA2D_Init(&DMA2D_InitStruct);
	DMA2D_StartTransfer();
	draws=1;
}

void LCDTFT::LCD_DrawLine(int xStart, int yStart, int xEnd, int yEnd, uint16_t Color)
{
	if(xStart > xEnd)
	{
		int temp = xEnd;
		xEnd = xStart;
		xStart = temp;
	}
	if(yStart > yEnd)
	{
		int temp = yEnd;
		yEnd = yStart;
		yStart = temp;
	}

	float rico = (float)(xEnd - xStart)/(float)(yEnd - yStart);
	if(rico == 0)
	{
		LCDTFT::LCD_DrawStraigtLine(xStart, yStart, yEnd - yStart, 0, Color);
		return;
	}
	if(rico >= 1000)
	{
		LCDTFT::LCD_DrawStraigtLine(xStart, yStart, xEnd - xStart, 1, Color);
		return;
	}

	float x = xStart;
	float y = yStart;
	int x2 = xStart;
	int y2 = yStart;
	if(rico >= 1)
	{
		while(x <= xEnd)
		{
			x += rico;
			int xTemp = ((int)x - x2)%(xEnd - x2);
			LCDTFT::LCD_DrawStraigtLine(x2, y2, xTemp, 0, Color);
			y2++;
			x2 += xTemp;
		}
	}
	else
	{
		rico = 1 / rico;
		while(y <= yEnd)
		{
			y += rico;
			int yTemp = ((int)y - y2)%(yEnd - y2);
			LCDTFT::LCD_DrawStraigtLine(x2, y2, yTemp, 1, Color);
			x2++;
			y2 += yTemp;
		}
	}
}

void LCDTFT::LCD_DrawBMP(int x, int y, uint32_t BmpAddress)
{
	/*Decompile the header (SIZE, INDEX, WIDTH, HEIGHT, BIT/PIXEL)*/
	uint32_t size = *(__IO uint32_t *) (BmpAddress);
	uint32_t index = *(__IO uint32_t *) (BmpAddress+4);
	uint32_t width = *(__IO uint32_t *) (BmpAddress+8);
	uint32_t height = *(__IO uint32_t *) (BmpAddress+12);
	uint32_t bitppixel = *(__IO uint32_t *) (BmpAddress+16);

	/*if(x+width>LCD_PIXEL_WIDTH)
		width = LCD_PIXEL_WIDTH - (x+width-LCD_PIXEL_WIDTH);*/
	if(y+height > LCD_PIXEL_HEIGHT)
		height = LCD_PIXEL_HEIGHT - (y+height-LCD_PIXEL_HEIGHT);

	int ImgSize = size - index;

	BmpAddress += index;
	uint32_t  Xaddress = CurrentFrameBuffer + 2*(LCD_PIXEL_WIDTH*y + x);

	while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET && draws !=0);

	DMA2D_InitTypeDef DMA2D_InitStruct;
	DMA2D_FG_InitTypeDef   DMA2D_FG_InitStruct;

	DMA2D_DeInit();
	DMA2D_InitStruct.DMA2D_Mode = DMA2D_M2M;
	if(bitppixel == 16)
		DMA2D_InitStruct.DMA2D_CMode = DMA2D_RGB565;
	DMA2D_InitStruct.DMA2D_OutputMemoryAdd = Xaddress;

	DMA2D_InitStruct.DMA2D_OutputOffset = LCD_PIXEL_WIDTH - width;
	DMA2D_InitStruct.DMA2D_NumberOfLine = height;
	DMA2D_InitStruct.DMA2D_PixelPerLine = width;

	DMA2D_InitStruct.DMA2D_OutputGreen = 0;
	DMA2D_InitStruct.DMA2D_OutputBlue = 0;
	DMA2D_InitStruct.DMA2D_OutputRed = 0;
	DMA2D_InitStruct.DMA2D_OutputAlpha = 0;

	DMA2D_Init(&DMA2D_InitStruct);
	DMA2D_FG_StructInit(&DMA2D_FG_InitStruct);

	DMA2D_FG_InitStruct.DMA2D_FGCM = CM_RGB565;
	DMA2D_FG_InitStruct.DMA2D_FGMA = BmpAddress;

	DMA2D_FGConfig(&DMA2D_FG_InitStruct);


	DMA2D_StartTransfer();
	draws=1;
}

void LCDTFT::LCD_DrawBMPLine(int x, int y, uint32_t address, int length, int bitppixel)
{

}

