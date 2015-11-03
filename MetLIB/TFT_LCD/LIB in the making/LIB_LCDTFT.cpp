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
	uint32_t  Xaddress = 0;

	Xaddress = CurrentFrameBuffer + 2*(LCD_PIXEL_WIDTH*y +x);

	/* Configure DMA2D */
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
	draws++;
}

void LCDTFT::LCD_DrawStraigtLine(int x, int y, int length, uint8_t Direction, uint16_t Color)
{
	while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET && draws !=0);
	DMA2D_InitTypeDef      DMA2D_InitStruct;

	uint32_t  Xaddress = 0;

	Xaddress = CurrentFrameBuffer + 2*(LCD_PIXEL_WIDTH*y + x);


	/* Configure DMA2D */
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
}


