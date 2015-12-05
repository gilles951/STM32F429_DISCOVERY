int main(void) {

	volatile int i;
    while (1) {


    	Writeport('G', 0xFFFF);
    	// Waste some time
    	for (i = 0; i < 5000000; i++);

    	// turn led off
    	Writeport('G', 0x0000);
    	// Waste some tome
        for (i = 0; i < 5000000; i++);
    }
}
