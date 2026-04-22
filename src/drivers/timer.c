#include "timer.h"

#include "arch/i386/io.h"
#include "src/scheduler/scheduler.h"

#define PIT_COMMAND 0x43
#define PIT_CHANNEL0 0x40
#define PIT_FREQUENCY 1193182

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
    update_sleep_tasks(timer_tick);
    outb(0x20, 0x20);
    loop_schedule();
}

// working with the timer frequency
void set_timer_frequency(uint32_t time){
    if(time < 10 || time > 1000){return;}
    timer_frequency = time;
    init_timer(time);
}

uint32_t get_timer_frequency(void){
    return timer_frequency;
}

// working with time
void sleep(uint32_t ms){
    uint32_t timer_tick_to_wait = (ms * timer_frequency) / 1000;

    current_task->wake_tick = timer_tick + timer_tick_to_wait;
    current_task->state_task = TASK_SLEEPING;

    loop_schedule();
}