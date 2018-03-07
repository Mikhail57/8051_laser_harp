#include "timers.h"

/*-------------------------
---------Timer 0-----------
-------------------------*/

static void timer0_isr(void) interrupt 1 using 1 {
	unsigned i;
	// Stop timer 0
	TR0 = 0;
	
	i = TIMER0_COUNT + TL0 + (TH0 << 8);
	
	TL0 = i;
	TH0 = i >> 8;
	
	// Start timer 0
	TR0 = 1;
	
	//Increnet timer tick
	timer0_tick++;
}

void timer0_initialize(void) {
	EA = 0; //Disable interrupts
	timer0_tick = 0;
	
	TR0 = 0; // Stop timer 0
	
	TMOD &= ~0x0F; // Clear timer 0 mode bits
	TMOD |= 0x01; // Put timer 0 into 16-bit
	
	TL0 = (TIMER0_COUNT & 0xFF);
	TH0 = TIMER0_COUNT >> 8;
	
	PT0 = 1;
	ET0 = 1;
	
	TR0 = 1;
	EA = 1;
}

unsigned timer0_count() {
	unsigned t;
	
	EA = 0;
	t = timer0_tick;
	EA = 1;
	
	return t;
}