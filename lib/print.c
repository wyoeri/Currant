#include "print.h"

#include "src/terminal/terminal.h"


void print_int(int n){
    char buf[12];
    int i = 0;

    if(0 == n){print_char('0'); return;}
    if(n < 0){print_char('-');}

    while(n > 0){
        buf[i++] = '0' + (n % 10);
        n /= 10; 
    }

    for(int j = i - 1; j >= 0; j--){
        print_char(buf[j]);
    }
}

void print_uint(uint32_t n){
    char buf[12];
    int i = 0;

    if(n < 0){return;}
    if(0 == n){print_char('0'); return;}

    while(n > 0){
        buf[i++] = '0' + (n % 10);
        n /= 10; 
    }

    for(int j = i - 1; j >= 0; j--){
        print_char(buf[j]);
    }
}

void print_hex(uint32_t n){
    /*static const char hex_table[] = "0123456789ABCDEF";
    print_str("0x");
    for(int i = 28; i >= 0; i -= 4){
        uint32_t res = (n >> i) & 0x0F;
        print_char(hex_table[res]);
    }*/  
}