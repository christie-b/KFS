#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel.h"
#include "source.h"
#include "keyboard.h"

 
/* Check if the compiler thinks you are targeting the wrong operating system. */
// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
// uint16_t* terminal_buffer;
size_t index;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
 
void kernel_main(void) 
{
	index = 0;
	/* Initialize terminal interface */
	terminal_initialize();

	// terminal_writestring("42\n");
    print_string("42\n", VGA_COLOR_RED);
    print_string("42\n", VGA_COLOR_BLUE);
	while (1) {


        keyboard_handler();


    }
    // print_string(" ___   ___    _______     \n", RED);
    // print_string("\\|\\  \\ |\\  \\  /  ___  \\    \n", RED);
    // print_string("\\ \\  \\_\\  \\/__/|_/  /|   \n", RED);
    // print_string(" \\ \\______  \\__|//  / /   \n", RED);
    // print_string("  \\|_____|\\  \\  /  /_/__  \n", RED);
    // print_string("         \\ \\__\\|\\________\\n", RED);
    // print_string("          \\|__| \\|_______|\n", RED);

}






// void kernel_main(void)
// {

//     terminal_buffer = (unsigned short*)VGA_ADDRESS;
//     vga_index = 0;

//     clear_screen();
//     print_string("Hello world!", YELLOW);
//     vga_index = 80;
//     print_string("Version 1", RED);
//     vga_index = 160;
//     print_char('b', RED);
//     vga_index = 240;
//     while (1) {


//         keyboard_handler();


//     }

//     return;
// }