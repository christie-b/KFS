#ifndef KERNEL_H
#define KERNEL_H 

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

# include "cursor.h"
# include "io.h"
# include "keyboard.h"
# include "kfunctions.h"
# include "shell.h"
# include "vga.h"

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

# define VGA_WIDTH 		25
# define VGA_HEIGHT 	80
# define VGA_COUNT 		25*80
# define VGA_ADDRESS 	0xB8000

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
// void print_string(char *str, unsigned char color);
// void print_char(char str, unsigned char color);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void kernel_main(void);

#endif