#include "commands.h"

#include "arch/i386/io.h"
#include "src/drivers/vga.h"
#include "src/terminal/terminal.h"
#include "lib/string/string.h"

typedef struct{
    const char* name;
    void(*func)(void);
} terminalcommand;

terminalcommand tcommand[] = {
    {"reboot", reboot},
    {"cat", cat},
    {"help", help},
    {"panic", panic},
    {"clear", clear_screen},
    {"black", black_theme},
    {"white", white_theme},
    {"green", green_theme},
    {"red", red_theme},
};

#define COMMAND_COUNT (sizeof(tcommand) / sizeof(terminalcommand))

void execute_command(char* command){
    if(NULL == command){return;}

    if('\0' == command[0]){return;}
    
    for(int i = 0; i < COMMAND_COUNT; i++){
        if(0 == strcom(command, tcommand[i].name)){
            tcommand[i].func();
            return;
        }
    }

    print_str(command);
    print_str(": command not found\n");
}

// system power control
void reboot(void){
    outb(0x64, 0xFE);
    while(1){__asm__ volatile("hlt");}
}

// output ascii cat
void cat(void){
    print_str("  /\\_/\\\n ( o.o )\n  > ^ <\n");
    print_str("meow\n");
}

// snow help information
void help(void){
    print_str("Commands:\n1. red\n2. green\n3. black\n4. white\n5. cat\n6. reboot\n7. panic\n");
    print_str("Creator: wyoeri\n");
    print_str("More information: https://github.com/wyoeri/Currant/tree/main \n");
}

// trigger kernel panic
void panic(void){
    __asm__ volatile("ud2");
}

// installing the theme
void black_theme(void){
    set_theme_terminal(WHITE_COLOR, BLACK_COLOR);
    clear_screen();
}

void white_theme(void){
    set_theme_terminal(BLACK_COLOR, WHITE_COLOR);
    clear_screen();
}

void red_theme(void){
    set_theme_terminal(BLACK_COLOR, RED_COLOR);
    clear_screen();
}

void green_theme(void){
    set_theme_terminal(BLACK_COLOR, GREEN_COLOR);
    clear_screen();
}