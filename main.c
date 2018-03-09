#include <reg52.h>

#define A1 0xF880
#define B1 0xF955
#define C1 0xFA00
#define D1 0xFAAB
#define E1 0xFB00
#define F1 0xFB80
#define G1 0xFC00

/*
Inverse order of bits in this way:
abcdefgh - efghabcd - ghefcdab - hgfedcba
*/
unsigned char invert(unsigned char b) {        
	b = ((b >> 4) & 15) | ((b & 15) << 4);
	b = ((b >> 2) & 51) | ((b & 51) << 2);
	b = ((b >> 1) & 85) | ((b & 85) << 1);
	return b;
}

unsigned char resValues;
unsigned char tone = 1;
unsigned start_count;
unsigned current_count;
unsigned diff;

sbit out = P3 ^ 4;
sbit lowPitch = P3 ^ 5;
sbit mediumPitch = P3 ^ 6;
sbit highPitch = P3 ^ 7;

sbit A = P2 ^ 7;
sbit _B = P2 ^ 6;
sbit C = P2 ^ 5;
sbit D = P2 ^ 4;
sbit E = P2 ^ 3;
sbit F = P2 ^ 2;
sbit G = P2 ^ 1;
sbit pitchButton = P2 ^ 0;

void setup() {
//	timer0_initialize();
	P2 = 0xFF;
//	start_count = timer0_count();
}

void delay(unsigned d) {
	TMOD = 0x01;
	TH0 = d >> 8;
	TL0 = d;
	TR0 = 1;
	while (TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void loop() {
	resValues = invert(P2); // assign to resValues reversed in numeric order values of photoresistors
	resValues = ~resValues; // Inverse values of resistors to match 1 -- high, 0 -- low
	P1 = resValues; // Display active notes on LEDs

	if ((P2 >> 1) != 0)
		out = ~out;
	
	if (A) {
		delay(0xF880);
	} else if (_B) {
		delay(0xF955);
	} else if (C) {
		delay(0xFA00);
	} else if (D) {
		delay(0xFAAB);
	} else if (E) {
		delay(0xFB00);
	} else if (F) {
		delay(0xFB80);
	} else if (G) {
		delay(0xFC00);
	} else {
		diff = 0;
	}
}

/*------------------------------------------------
MAIN C Function
------------------------------------------------*/

void main (void) {
	setup();
	
	while (1) 
		loop();
}
