#include "scheduler.h"

#include "lib/data_structures/ringbuffer.h"
#include "src/memory/kmalloc.h"

volatile task_t* current_task = NULL;
volatile uint32_t pid_count = 1;

void init_schedule(void){
    current_task = (task_t*)kcalloc(1, sizeof(task_t));
    current_task->pid_task = 0;
    current_task->next_task = current_task;
    current_task->state_task = TASK_RUNNING;
}

// main schedule loop
void loop_schedule(void){
    if(NULL == current_task){return;}

    task_t* prev = current_task;
    task_t* next = current_task->next_task;

    while(next->state_task != TASK_READY && next->state_task != TASK_RUNNING){
        next = next->next_task;

        if(next == current_task){break;}
    }

    if(next == prev){
        if(TASK_SLEEPING == prev->state_task){
            __asm__ volatile("sti; hlt");
            return;
        }
        return;
    }

    if(TASK_RUNNING == prev->state_task){
        prev->state_task = TASK_READY;
    }
    next->state_task = TASK_RUNNING;
    current_task = next;

    switch_context(&(prev->kernel_stack_task), next->kernel_stack_task);
}

// working with tasks
task_t* create_task(void(*func)(void)){
    task_t* new_task = (task_t*)kcalloc(1, sizeof(task_t));
    uint32_t size_stack = 4096;
    uint32_t* stack = (uint32_t*)kmalloc(size_stack);
    uint32_t* esp = (uint32_t*)(((uint32_t)stack + size_stack) & ~0xF);

    *(--esp) = (uint32_t)func;
    *(--esp) = 0; // ebp
    *(--esp) = 0; // ebx
    *(--esp) = 0; // esi
    *(--esp) = 0; // edi

    new_task->pid_task = pid_count++;
    new_task->state_task = TASK_READY;
    new_task->kernel_stack_task = (uint32_t)esp;
    new_task->next_task = current_task->next_task;
    current_task->next_task = new_task;

    return new_task;
}

void exit_task(void){
    __asm__ volatile("cli");

    current_task->state_task = TASK_ZOMBIE;
    loop_schedule();

    while(1){__asm__ volatile("hlt");}
}

void update_sleep_tasks(uint32_t current_timer_tisk){
    if(NULL == current_task){return;}

    task_t* start = current_task;
    task_t* current = start;

    do{
        if(TASK_SLEEPING == current->state_task && current_timer_tisk >= current->wake_tick){
            current->state_task = TASK_READY;
        }
        current = current->next_task;
    } while(current != start);
}