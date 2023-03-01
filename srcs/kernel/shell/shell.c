#include "shell.h"
#include "../keyboard/keyboard.h"
#include "../kfunctions/kfunctions.h"
#include "../vga/vga.h"

static void move_right_buffer(char *buffer, int size, int index)
{
    while (size > index)
    {
        buffer[size] = 0;
        buffer[size] = buffer[size - 1];
        size--;
    }

}

static void move_left_buffer(char *buffer, int size, int index)
{
    while (index < size)
    {
        buffer[index] = 0;
        buffer[index] = buffer[index + 1];
        index++;
    }

}

void get_line(char *buffer, unsigned int buffer_limit)
{
    char                key = 0;
    unsigned int        i = 0;

    while (1)
    {
        key = last_char();
        if (key == 0)
        {
            continue;
        }
        else if (key < 0)
        {
            if (key == LEFT_ARROW)
            {
                if (i > 0)
                {
                    move_cursor_left(1);
                    i--;
                }
            }
            else if (key == RIGHT_ARROW)
            {
                if (i < k_strlen(buffer))
                {
                    move_cursor_right(1);
                    i++;
                }
            }
            continue;
        }
        if (key == '\n')
        {
            k_putchar(key, VGA_COLOR_WHITE);
            return;
        }
        if (GET_STATUS(keystatus_getter(), CONTROL_BIT))
        {
            if (key == 'l')
            {
                k_memset(buffer, 0, 256);
                clear_screen();
                return;
            }
        }
        if (key == '\b')
        {
            if (k_strlen(buffer) > 0 && i > 0)
            {
                clear_previous_char();
                buffer[i - 1] = 0;
                i--;
                move_left_buffer(buffer, buffer_limit, i);
            }
        }
        else
        {
            k_putchar(key, VGA_COLOR_WHITE);
            move_right_buffer(buffer, buffer_limit, i);
            buffer[i] = key;
            if (k_strlen(buffer) == buffer_limit)
            {
                return;
            }
            i++;
        }
    }
}

void init_shell()
{
    char buffer[256];
    while (1)
    {
        k_putstr("42> ", VGA_COLOR_BLUE);
        k_memset(buffer, 0, 256);
        get_line(buffer, 256);
        if (k_strlen(buffer) > 0)
        {
            if (k_strcmp(buffer, "clear") == 0)
            {
                clear_screen();
            }
        }
    }
}