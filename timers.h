#ifndef TIMER0_COUNT
#define TIMER0_COUNT 0xFFAD /* 10000h - ((12,000,000 Hz / (12 * FREQ)) - 17); FREQ=10,000 Hz */
#endif

#ifndef TIMER1_COUNT
#define TIMER1_COUNT 0xFFAD /* 10000h - ((12,000,000 Hz / (12 * FREQ)) - 17); FREQ=10,000 Hz */
#endif

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <reg52.h>

/*-------------------------
---------Timer 0-----------
-------------------------*/
static unsigned timer0_tick;


static void timer0_isr(void);

void timer0_initialize(void);

unsigned timer0_count();

//TODO: Add Timer 1

#endif