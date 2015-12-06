/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "usb_cdc_device/tm_stm32f4_usb_vcp.h"
//#include "tm_stm32f4_disco.h"
#include "defines.h"

int main(void) {
    uint8_t c;
    /* System Init */
    SystemInit();

    /* Initialize LED's. Make sure to check settings for your board in tm_stm32f4_disco.h file */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //
    	GPIO_InitTypeDef GPIO_InitDef;

    GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14; // we gaan pin 13 en 14 gebruiken

    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;		// init push-pull
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 		// init output
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;	// init no pullup
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;	// init 100 MHZ

    //Initialize pins
    GPIO_Init(GPIOG, &GPIO_InitDef);
    GPIO_ToggleBits(GPIOG, GPIO_Pin_13);


    /* Initialize USB VCP */
    TM_USB_VCP_Init();

    while (1) {
        /* USB configured OK, drivers OK */
        if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) {
            /* Turn on GREEN led */
            //TM_DISCO_LedOn(LED_GREEN);
            //TM_DISCO_LedOff(LED_RED);
            /* If something arrived at VCP */
            if (TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK) {
                /* Return data back */
                TM_USB_VCP_Putc('0' + (c /100) % 10);
                TM_USB_VCP_Putc('0' + (c /10) % 10);
                TM_USB_VCP_Putc('0' + c % 10);
                TM_USB_VCP_Putc(',');
                TM_USB_VCP_Putc(' ');
                GPIO_ToggleBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);
            }
            else
            {
            	//TM_USB_VCP_Putc(' ');
            }
        } else {
            /* USB not OK */
            //TM_DISCO_LedOff(LED_GREEN);
            //TM_DISCO_LedOn(LED_RED);
        }
    }
}
