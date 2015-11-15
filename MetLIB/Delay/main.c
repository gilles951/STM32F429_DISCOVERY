

#include "compact_lib_stm32f4.h" // Voeg alle nodig functies in.
#include "tm_stm32f4_delay.h"
int i = 0 ;

int main(void) {
	TM_DELAY_Init();
    while (1) {
    // turn led on
    	GPIO_write_led(LED_RED,on);

   // Waste some time
    	Delayms(100);

   // turn led off
    GPIO_write_led(LED_RED,off);
    // Waste some time
        Delayms(100);

    }
}
