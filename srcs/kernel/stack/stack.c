# include "stack.h"

// #include <ctype.h>

int isprint(int c) {
    return (c >= 32 && c <= 126);
}

void print_memory(const uintptr_t addr, size_t size)
{
    const unsigned char *ptr = (unsigned char*)addr;
    char buf[50];
    int pos = 0;

    for (size_t i = 0; i < size; ++i, ++ptr) {
        if (i % 16 == 0) {
            pos = 0;
            pos += (int)k_itoa_x((uint32_t)ptr, buf + pos, 16);
            k_putstr("0x", VGA_COLOR_WHITE);
            k_putstr(buf, VGA_COLOR_WHITE);
            k_putchar(' ', VGA_COLOR_WHITE);
        }

        pos += (int)k_itoa_x(*ptr, buf + pos, 16);
        if ((i & 0x1) != 0) {
            k_putchar(' ', VGA_COLOR_WHITE);
        }
        if ((i + 1) % 16 == 0) {
            k_putchar(' ', VGA_COLOR_WHITE);
            for (size_t j = 0; j < 16; j++) {
                if (isprint(*(ptr - 15 + j))) {
                    k_putchar(*(ptr - 15 + j), VGA_COLOR_WHITE);
                } else {
                    k_putchar('.', VGA_COLOR_WHITE);
                }
            }
            k_putchar('\n', VGA_COLOR_WHITE);
        }
    }

    if (size % 16 != 0) {
        for (size_t i = 0; i < 16 - size % 16; i++) {
            k_putstr("   ", VGA_COLOR_WHITE);
            if ((i & 0x1) != 0) {
                k_putchar(' ', VGA_COLOR_WHITE);
            }
        }

        k_putchar(' ', VGA_COLOR_WHITE);
        for (size_t i = 0; i < size % 16; i++) {
            if (isprint(*(ptr - size % 16 + i))) {
                k_putchar(*(ptr - size % 16 + i), VGA_COLOR_WHITE);
            } else {
                k_putchar('.', VGA_COLOR_WHITE);
            }
        }
        k_putchar('\n', VGA_COLOR_WHITE);
    }
}
