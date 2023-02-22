#ifndef VGA_H
#define VGA_H

#include "../kernel.h"

extern unsigned short* 	terminal_buffer;
extern unsigned int 	vga_index;

void            clear_screen();
void            move_left(int nb);
void            move_right(int nb);
void            clear_previous_char();
void            set_vga_index(unsigned int index);

#endif