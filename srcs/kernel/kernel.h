#ifndef KERNEL_H
#define KERNEL_H 

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

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