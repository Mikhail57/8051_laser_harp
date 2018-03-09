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
unsigned char tone = 0;
unsigned diff;

sbit out = P3 ^ 4;
sbit lowTone = P3 ^ 5;
sbit mediumTone = P3 ^ 6;
sbit highTone = P3 ^ 7;

sbit A = P2 ^ 7;
sbit _B = P2 ^ 6;
sbit C = P2 ^ 5;
sbit D = P2 ^ 4;
sbit E = P2 ^ 3;
sbit F = P2 ^ 2;
sbit G = P2 ^ 1;
sbit toneButton = P2 ^ 0;

void setup() {
//	timer0_initialize();
	P2 = 0xFF;
//	start_count = timer0_count();
}

void delay(unsigned d) {
	TMOD = 0x01; // 16-bit mode for 1st timer
	TH0 = d >> 8; // high bits
	TL0 = d; // low bits
	TR0 = 1; // enable 1st timer
	while (TF0 == 0); // Wait for flag
	TR0 = 0; // disable timer
	TF0 = 0; // Clean flag
}

void showTone(char tone) {
	lowTone = 0;
	mediumTone = 0;
	highTone = 0;
	if (tone == 0)
		lowTone = 1;
	else if (tone == 1)
		mediumTone = 1;
	else if (tone == 2)
		highTone = 1;
}

void loop() {
	resValues = invert(P2); // assign to resValues reversed in numeric order values of photoresistors
	resValues = ~resValues; // Inverse values of resistors to match 1 -- high, 0 -- low
	P1 = resValues; // Display active notes on LEDs

	if (toneButton)
		tone = (tone + 1) % 3;
	
	showTone(tone);
	
	if ((P2 >> 1) != 0)
		out = ~out;
	
	if (A) {
		delay(A1);
	} else if (_B) {
		delay(B1);
	} else if (C) {
		delay(C1);
	} else if (D) {
		delay(D1);
	} else if (E) {
		delay(E1);
	} else if (F) {
		delay(F1);
	} else if (G) {
		delay(G1);
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
