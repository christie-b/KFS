#include "vga.h"


unsigned short   *terminal_buffer = (unsigned short *)VGA_ADDRESS;
unsigned int     vga_index = 0;

void set_vga_index(unsigned int index)
{
    vga_index = index;

    if (vga_index >= VGA_WIDTH * VGA_HEIGHT)
    {
        set_cursor_pos((uint16_t)((VGA_WIDTH * VGA_HEIGHT) - VGA_WIDTH) + (vga_index % VGA_WIDTH));
    }
    else
    {
        set_cursor_pos((uint16_t)vga_index);
    }
}


void clear_screen()
{
    int i = 0;
    while (i < VGA_COUNT* 2)
    {
        terminal_buffer[i] = BLANK;
        i++;
    }
    set_vga_index(0);
}

void clear_previous_char()
{
    if (vga_index - 1 > 0)
    {
        set_vga_index(vga_index - 1);
        terminal_buffer[vga_index] = BLANK;
        move_left();
    }
}

void move_right()
{
    unsigned int last;

    last = VGA_COUNT;
    while (last > vga_index)
    {
        terminal_buffer[last] = BLANK;
        terminal_buffer[last] = terminal_buffer[last - 1];
        last--;
    }

}

void move_left()
{
    unsigned int cur;

    cur = vga_index;
    while (cur < VGA_COUNT)
    {
        terminal_buffer[cur] = BLANK;
        terminal_buffer[cur] = terminal_buffer[cur + 1];
        cur++;
    }

}

void move_cursor_right(int nb)
{
    set_vga_index(vga_index + nb);
}

void move_cursor_left(int nb)
{
    set_vga_index(vga_index - nb);
}