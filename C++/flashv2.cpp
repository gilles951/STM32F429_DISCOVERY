int main(void) {
 GPIO test('a',13);
 GPIO_Gate poortG('G',0x0000);
 test.OType(GPIO_OType_OD);
	volatile int i;
    while (1) {


    	poortG.Writeport(0x0000);
    	// Waste some time
    	for (i = 0; i < 5000000; i++);

    	// turn led off
    	poortG.Writeport(0xFFFF);
    	// Waste some time
        for (i = 0; i < 5000000; i++);
    }
}
