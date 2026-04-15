#include "terminal.h"

#include "src/drivers/vga.h"
#include "src/drivers/keyboard.h"
#include "src/terminal/commands.h"

typedef struct{
    int x;
    int y;
} terminalcursor;

static terminalcursor tcs;
static char buffer_term[TERMINAL_BUFFER_SIZE];
static int index_term = 0;
static uint8_t theme_terminal = DEFAULT_THEME;

void init_terminal(void){
    tcs.x = 0;
    tcs.y = 0;
}

// linear printing
void print_char(const char c){
    if('\n' == c){
        tcs.x = 0; 
        tcs.y++;
    }
    else if('\t' == c){
        tcs.x += 4;
    }
    else if('\b' == c && tcs.x > 0){
        tcs.x--;
        put_vga(' ', theme_terminal, tcs.x, tcs.y);
    }
    else{
        put_vga(c, theme_terminal, tcs.x, tcs.y);
        tcs.x++;
    }

    if (tcs.x >= 80) {
        tcs.x = 0;
        tcs.y++;
    }

    if (tcs.y >= 25) {
        clear_screen();
        tcs.x = 0;
        tcs.y = 0;
    }
}

void print_str(const char* s){
    while('\0' != *s){
        print_char(*s);
        s++;
    }
}

// printing by coordinates
void print_coord_char(const char c, int x, int y){
    tcs.y = y;
    tcs.x = x;
    put_vga(c, theme_terminal, x, y);
}

void print_coord_str(const char* s, int x, int y){
    tcs.y = y;
    tcs.x = x;
    while('\0' != *s){
        put_vga(*s, theme_terminal, x, y);
        s++;
    }
}

// processing user input
void input_processing_terminal(void){
    int sc = get_scancode_keyboard();

    if(-1 == sc){return;}
    if(sc & 0x80){return;}

    char c = kbd_us[sc];
    if(0 == c){return;}

    if('\n' == c){
        print_char('\n');
        buffer_term[index_term] = '\0';
        execute_command(buffer_term);
        output_invitation();
        index_term = 0;
    }
    else if('\b' == c){
        if(index_term > 0){
           buffer_term[--index_term] = '\0';
           print_char('\b'); 
        }
    }
    else if(index_term < TERMINAL_BUFFER_SIZE - 1){
        buffer_term[index_term++] = c;
        print_char(c); 
    }
}

// working whith colors
uint8_t get_theme_terminal(void){
    return theme_terminal;
}

void set_theme_terminal(uint8_t fg, uint8_t bg){
    uint8_t color = make_color_terminal(fg, bg);
    theme_terminal = color;
}

uint8_t make_color_terminal(uint8_t fg, uint8_t bg){
    return (bg << 4) | fg;
}

// other
void output_invitation(void){
    print_str("$ ");
}

void clear_screen(void){
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 80; j++){
            put_vga(' ', theme_terminal, j, i);
        }
    }
    tcs.x = 0;
    tcs.y = 0;
}