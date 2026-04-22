#ifndef TIMER_H
#define TIMER_H

#include "lib/other/types.h"

#define DEFAULT_TIMER_FREQUENCY 250

extern volatile uint32_t timer_frequency;

// working with a timer
void init_timer(uint32_t frequency);
void handler_timer(void);

// working with the timer frequency
void set_timer_frequency(uint32_t time);
uint32_t get_timer_frequency(void);

// working with time
void sleep(uint32_t ms);

#endif