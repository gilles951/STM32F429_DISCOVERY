/**
 *	Keil project for USB HID Device
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "usb_hid_device/tm_stm32f4_usb_hid_device.h"
//#include "usb_hid_device/usbd_cdc_core.h"

USB_OTG_CORE_HANDLE	USB_OTG_dev;

static void SetSYSCLK_168(void)
{
  /* Select HSE as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

  /* Wait till HSE is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x04)
  {}

  /* Disable PLL */
  RCC_PLLCmd(DISABLE);

  /* Disable Over-drive mode */
  PWR_OverDriveCmd(DISABLE);
  PWR_OverDriveSWCmd(DISABLE);

  /* Wait till ODSWRDY is reset */
  while (PWR_GetFlagStatus(PWR_FLAG_ODSWRDY) != RESET)
  {}

  /* Configure PLL clock to have:
  PLL_VCO = (HSE_VALUE / PLL_M) * PLL_N = 336 MHz
  SYSCLK = PLL_VCO / PLL_P = 168 MHz
  USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ = 48 MHz
  */
  RCC_PLLConfig(RCC_PLLSource_HSE,
                8, //PLLM
                336, //PLLN
                2, //PLLP
                7 //PLLQ
                  );

  /* Enable PLL */
  RCC_PLLCmd(ENABLE);

  /* Wait till PLL is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}

  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /* Wait till PLL is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x08)
  {}

  /* Update SystemCoreClock global variable value */
  SystemCoreClock = 168000000;
}

int main(void)
{
	//USBD_Init(&USB_OTG_dev, USB_OTG_HS_CORE_ID, &USR_desc, &USBD_HID_cb, &USR_cb);
	SetSYSCLK_168();


	uint8_t already = 0;

	/* Set structs for all examples */
	TM_USB_HIDDEVICE_Keyboard_t Keyboard;
	TM_USB_HIDDEVICE_Gamepad_t Gamepad1, Gamepad2;
	TM_USB_HIDDEVICE_Mouse_t Mouse;

	/* Initialize system */
	SystemInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); // turns the clock on for register G
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // turns the clock on for register A
	GPIO_InitTypeDef GPIO_InitDef;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;	// init pin 13 for use
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// init push-pull
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;				// init output
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz

	//Initialize pins
	GPIO_Init(GPIOG, &GPIO_InitDef);

	GPIO_InitDef.GPIO_Pin =  GPIO_Pin_0;				// init pin 13 for use
	GPIO_InitDef.GPIO_OType = GPIO_OType_OD;			// init open drain
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;				// init input
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;			// init no pullup
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;		// init 100 Mhz


	//Initialize pins
	GPIO_Init(GPIOA, &GPIO_InitDef);

	/* Initialize USB HID Device */
	TM_USB_HIDDEVICE_Init();

	/* Set default values for mouse struct */
	TM_USB_HIDDEVICE_MouseStructInit(&Mouse);
	/* Set default values for keyboard struct */
	TM_USB_HIDDEVICE_KeyboardStructInit(&Keyboard);
	/* Set default values for gamepad structs */
	TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad1);
	TM_USB_HIDDEVICE_GamepadStructInit(&Gamepad2);

	while (1) {
		/* If we are connected and drivers are OK */
		if (TM_USB_HIDDEVICE_GetStatus() == TM_USB_HIDDEVICE_Status_Connected) {
			/* Turn on green LED */
			GPIO_WriteBit(GPIOG, GPIO_Pin_13, 1);


/* Simple sketch start */

			/* If you pressed button right now and was not already pressed */
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) && already == 0) { /* Button on press */
			    already = 1;

			    /* Send "Tilen" to computer */

			    /* First we need upper "T" */
			    //Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Pressed; /* Left shift is pressed */
			    Keyboard.Key1 = 0x17;    /* 0x17 = T */
			    /* Send keyboard report */
			    TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
			    GPIO_WriteBit(GPIOG, GPIO_Pin_14, 1);
			    int i = 0;
			    for(i = 0; i < 5000000; i++);
			    Keyboard.Key1 = 0x00;    /* 0x17 = T */
			    /* Send keyboard report */
			    TM_USB_HIDDEVICE_KeyboardSend(&Keyboard);
			    //TM_USB_HIDDEVICE_KeyboardReleaseAll();
			    GPIO_WriteBit(GPIOG, GPIO_Pin_14, 0);

			} else if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) && already == 1) { /* Button on release */
			    already = 0;

			    //Keyboard.L_GUI = TM_USB_HIDDEVICE_Button_Released; /* Left shift is pressed */
			    //Keyboard.Key1 = 0x00;    /* 0x17 = T */
			    /* Send keyboard report */
			    //TM_USB_HIDDEVICE_KeyboardReleaseAll();
			    //GPIO_WriteBit(GPIOG, GPIO_Pin_14, 0);
			}

/* Simple sketch end */

		} else {
			/* Turn off green LED */
			GPIO_WriteBit(GPIOG, GPIO_Pin_13, 0);

		}
	}
}
