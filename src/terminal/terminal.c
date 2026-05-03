#include "terminal.h"

#include "src/drivers/vga.h"
#include "src/drivers/keyboard.h"
#include "src/terminal/commands.h"

#define SIZE_COL 25 // y
#define SIZE_ROW 80 // x

typedef struct{
    int x;
    int y;
} terminalcursor_t;

static terminalcursor_t tcs;
static char buffer_term[TERMINAL_BUFFER_SIZE];
static int index_term = 0;
static uint8_t theme_terminal = DEFAULT_THEME;

void init_terminal(void){
    tcs.x = 0;
    tcs.y = 0;
    clear_screen();
    output_invitation();
}

// linear printing
void print_char(const char c){
    char_handler(c);
}

void print_str(const char* s){
    while('\0' != *s){
        char_handler(*s);
        s++;
    }
}

// printing by coordinates
void print_coord_char(const char c, const int x, const int y){
    tcs.y = y;
    tcs.x = x;
    put_vga(c, theme_terminal, tcs.x, tcs.y);
}

void print_coord_str(const char* s, const int x, const int y){
    tcs.y = y;
    tcs.x = x;
    while('\0' != *s){
        put_vga(*s, theme_terminal, tcs.x, tcs.y);
        tcs.x++;
        s++;
    }
}

// processing user input
void input_processing_terminal(void){
    char c = get_char_keyboard();
    if(0 == c || '\t' == c){return;}

    if('\n' == c){
        char_handler('\n');
        buffer_term[index_term] = '\0';
        execute_command(buffer_term);
        index_term = 0;
        output_invitation();
    }
    else if('\b' == c){
        if(index_term > 0){
           buffer_term[--index_term] = '\0';
           char_handler('\b'); 
        }
    }
    else if(index_term < TERMINAL_BUFFER_SIZE - 1){
        buffer_term[index_term++] = c;
        char_handler(c); 
    }
}

void char_handler(const char c){
    if('\n' == c){
        tcs.x = 0; 
        tcs.y++;
    }
    else if('\b' == c){
        if(tcs.x > 0){
            tcs.x--;
            put_vga(' ', theme_terminal, tcs.x, tcs.y);
        }
    }
    else{
        put_vga(c, theme_terminal, tcs.x, tcs.y);
        tcs.x++;
    }

    if(tcs.x >= SIZE_ROW){
        tcs.x = 0;
        tcs.y++;
    }

    if(tcs.y >= SIZE_COL){
        clear_screen();
    }
}

// working whith colors
uint8_t get_theme_terminal(void){
    return theme_terminal;
}

void set_theme_terminal(const uint8_t fg, const uint8_t bg){
    theme_terminal = make_color_terminal(fg, bg);
}

uint8_t make_color_terminal(const uint8_t fg, const uint8_t bg){
    return (bg << 4) | fg;
}

// other
void output_invitation(void){
    print_str("> ");
}

void clear_screen(void){
    for(int i = 0; i < SIZE_COL; i++){
        for(int j = 0; j < SIZE_ROW; j++){
            put_vga(' ', theme_terminal, j, i);
        }
    }
    tcs.x = 0;
    tcs.y = 0;
}