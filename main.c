#include <reg52.h>
#include "timers.h"

#define A1 182
#define B1 161
#define C1 153
#define D1 136
#define E1 121
#define F1 114
#define G1 102

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

sbit P3_4 = P3 ^ 4;

sbit A = P2 ^ 7;
sbit _B = P2 ^ 6;
sbit C = P2 ^ 5;
sbit D = P2 ^ 4;
sbit E = P2 ^ 3;
sbit F = P2 ^ 2;
sbit G = P2 ^ 1;
sbit pitchButton = P2 ^ 0;

void setup() {
	timer0_initialize();
	P2 = 0xFF;
	start_count = timer0_count();
}

void loop() {
	resValues = invert(P2); // assign to resValues reversed in numeric order values of photoresistors
	resValues = ~resValues; // Inverse values of resistors to match 1 -- high, 0 -- low
	P1 = resValues; // Display active notes on LEDs

	if (A)
		diff = A1;
	else if (_B)
		diff = B1;
	else if (C)
		diff = C1;
	else if (D)
		diff = D1;
	else if (E)
		diff = E1;
	else if (F)
		diff = F1;
	else if (G)
		diff = G1;
	else diff = 0;
	
	current_count = timer0_count();
	if ((diff != 0) && (current_count - start_count <= diff)) {
		start_count = current_count;
		P3_4 ^= 1;
	} else {
		P3_4 = 0;
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
