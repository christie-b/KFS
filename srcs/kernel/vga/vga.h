#ifndef VGA_H
#define VGA_H

#include "../kernel.h"

extern unsigned short* 	terminal_buffer;
extern unsigned int 	vga_index;

void            newline();
void            move_left();
void            scroll_up();
void            move_right();
void            clear_screen();
void            clear_line(int line);
void            clear_previous_char();
void            move_cursor_left(int nb);
void            move_cursor_right(int nb);
void            copy_line(int dst, int src);
void            set_vga_index(unsigned int index);

#endif