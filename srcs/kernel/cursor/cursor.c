#include "cursor.h"
#include "../io/io.h"

uint16_t get_cursor_pos()
{
    uint16_t pos = 0;
    outb (0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

void set_cursor_pos(uint16_t pos)
{
    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8));
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

//https://wiki.osdev.org/Text_Mode_Cursor
