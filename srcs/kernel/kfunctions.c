#include "source.h"

void k_putchar(char c)
{
    if (c == '\n')
    {
        newline();
    }
    else
    {
        move_right();
        terminal_buffer[vga_index] = (unsigned short) c;
        vga_index++;
    }
}

void k_putstr(char *str)
{
    int i = 0;
    while (str[i])
    {
        k_putchar(str[i]);
        i++;
    }
}

//git clone https://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@github.com/christie-b/KFS.git