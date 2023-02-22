#ifndef SOURCE_H
#define SOURCE_H

#include "kfunctions.h"
#define VGA_ADDRESS 0xB8000   

extern unsigned short* terminal_buffer;
extern unsigned int vga_index;

void print_string(char* str, unsigned char color);
void print_char(char str, unsigned char color);
void clear_screen(void);
uint16_t get_cursor_pos();
void set_cursor_pos(uint16_t pos);

#endif