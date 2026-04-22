#ifndef COMMANDS_H
#define COMMANDS_H

void execute_command(char* command);

// system power control
void reboot(void);

// output ascii cat
void cat(void);

// snow help information
void help(void);

// trigger kernel panic
void panic(void);

// installing the theme
void black_theme(void);
void white_theme(void);
void red_theme(void);
void green_theme(void);
void blue_theme(void);

#endif