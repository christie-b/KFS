#ifndef VGA_H
#define VGA_H

#include "../kernel.h"

extern unsigned short* 	terminal_buffer;
extern unsigned int 	vga_index;

/* Hardware text mode color constants. */
enum vga_color
{
	VGA_COLOR_BLACK 		= 0,
	VGA_COLOR_BLUE 			= 1,
	VGA_COLOR_GREEN 		= 2,
	VGA_COLOR_CYAN 			= 3,
	VGA_COLOR_RED 			= 4,
	VGA_COLOR_MAGENTA 		= 5,
	VGA_COLOR_BROWN 		= 6,
	VGA_COLOR_LIGHT_GREY 	= 7,
	VGA_COLOR_DARK_GREY 	= 8,
	VGA_COLOR_LIGHT_BLUE 	= 9,
	VGA_COLOR_LIGHT_GREEN 	= 10,
	VGA_COLOR_LIGHT_CYAN 	= 11,
	VGA_COLOR_LIGHT_RED 	= 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN 	= 14,
	VGA_COLOR_WHITE 		= 15,
};

# define VGA_WIDTH 		80
# define VGA_HEIGHT 	25
# define VGA_COUNT 		25*80
# define VGA_ADDRESS 	0xB8000
# define BLANK ' ' | (((VGA_COLOR_BLACK << 4) | (VGA_COLOR_WHITE & 0x0F)) << 8)

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