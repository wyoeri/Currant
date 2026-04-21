#include "timer.h"

#include "arch/i386/io.h"

#define PIT_COMMAND 0x43
#define PIT_CHANNEL0 0x40
#define PIT_FREQUENCY 1193182
#define DEFAULT_TIMER_FREQUENCY 100

volatile uint32_t timer_tick = 0;
volatile uint32_t timer_frequency = DEFAULT_TIMER_FREQUENCY;

// working with a timer
void init_timer(uint32_t frequency){
    timer_frequency = frequency;
    uint32_t divisor =  PIT_FREQUENCY / frequency;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t)(divisor >> 8) & 0xFF);
}

void handler_timer(void){
    timer_tick++;
    outb(0x20, 0x20);
}

// working with the timer frequency
void set_timer_frequency(uint32_t time){
    timer_frequency = time;
}

uint32_t get_timer_frequency(void){
    return timer_frequency;
}

// working with time
void sleep(uint32_t ms){
    uint32_t timer_tick_to_wait = ms / (1000 / timer_frequency);

    uint32_t start_timer_tick = timer_tick;
    uint32_t end_timer_tick = start_timer_tick + timer_tick_to_wait;

    while(timer_tick < end_timer_tick){
        __asm__ volatile("hlt");
    }
}