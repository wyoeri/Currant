#include "terminal.h"

#include "src/drivers/vga.h"
#include "src/drivers/keyboard.h"
#include "src/terminal/commands.h"
#include "lib/string.h"
#include "lib/types.h"

static char buffer_term[TERMINAL_BUFFER_SIZE];
static int index_term = 0;

void terminal(void){
    int sc = get_scancode_keyboard();

    if(-1 == sc){return;}
    if(sc & 0x80){return;}

    char c = kbd_us[sc];
    if(0 == c){return;}

    if('\n' == c){
        print_char_vga('\n');
        buffer_term[index_term] = '\0';
        execute_command();
        index_term = 0;
    }
    else if('\b' == c){
        if(index_term > 0){
           buffer_term[index_term--] = '\0';
           print_char_vga('\b'); 
        }
    }
    else if(index_term < 127){
        buffer_term[index_term++] = c;
        print_char_vga(c); 
    }
}

void output_invitation(void){
    print_str_vga("wymeow $ ");
}

void execute_command(void){
    if(0 == index_term){
        output_invitation();
    }
    else if(0 == strcom(buffer_term, "reboot")){
        reboot();
    }
    else if(0 == strcom(buffer_term, "cat")){
        cat();
    }   
    else if(0 == strcom(buffer_term, "help")){
        help();
    }
    else if(0 == strcom(buffer_term, "panic")){
        panic();
    }
    else if(0 == strcom(buffer_term, "clear")){
        clear_screen_vga();
    }
    else{
        print_str_vga(buffer_term);
        print_str_vga(" : command not found\n");
    }
    output_invitation();
}