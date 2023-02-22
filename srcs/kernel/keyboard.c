// const unsigned char keyboard_mapping[128] =
// {
//   0,
//   27, // ascii code for escape key
//   '1','2','3','4','5','6','7','8','9','0','-','=',
//   '\b', // Backspace
//   '\t', // Tab
//   'q','w','e','r','t','y','u','i','o','p','[',']',
//   '\n', // Enter
//   0, // left Ctrl
//   'a','s','d','f','g','h','j','k','l',';','\'','`',
//   0, // left Shift
//   '\\','z','x','c','v','b','n','m',',','.','/',
//   0, // right Shift
//   '*', // numpad asterisk
//   0, // left Alt
//   ' ', // Spacebar
//   0,
// };
// https://stackoverflow.com/questions/2746817/what-does-the-0x80-code-mean-when-referring-to-keyboard-controls
//https://forum.osdev.org/viewtopic.php?f=1&t=28437#:~:text=To%20get%20input%20from%20the,to%20terminate%20the%20interrupt%20cleanly.

#include "kernel.h"  
#include "keyboard.h"  
#include "source.h"
#include "io.h"

char last = 0;
char keystatus = 0;
int clicked = 0;
int canSend = 0;

static char keyboard_mapping[128] =
{
	0, 0, '&', 0, '"', '\'', '(', 0, 0, '!', 0, 0, ')', '-', '\b', 0, 'a', 'z',
    'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0, 'q', 's', 'd',
    'f', 'g', 'h', 'j', 'k', 'l', 'm', 0, '<', 0, '`', 'w', 'x', 'c', 'v', 'b',
    'n', ',', ';', ':', '=', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', '6',
	0, 0, 0, 0, 0
};
static char keyboard_shift_mapping[128] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, '_', '\b', 0,
    'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, '*', '\n', 0, 'Q', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', '>', 0, 0, 'W', 'X', 'C', 'V',
    'B', 'N', '?', '.', '/', '+', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    '6', 0, 0, 0, 0, 0
};

uint16_t keyboard_handler()
{
    uint16_t scancode = 0;

    scancode = inb(0x60);
    if (RELEASED(scancode)) // Key is realeased
    {
        if (keyboard_mapping[GET_RELEASED_KEY(scancode)] == SHIFT)
        {
                UNSET_STATUS(keystatus, SHIFT_BIT);
        }
        else if (keyboard_mapping[GET_RELEASED_KEY(scancode)] == CONTROL)
        {
            UNSET_STATUS(keystatus, CONTROL_BIT);
        }
        return ;
    }
    else // Key is pressed
    {
        outb(0x60, 0);
        // Between 0 and 128 
        if (scancode > 128)
        {
            return ;
        }
        // Special Keys : shift, control, capslock
        if (keyboard_mapping[scancode] == SHIFT)
        {
            SET_STATUS(keystatus, SHIFT_BIT);
        }
        else if (keyboard_mapping[scancode] == CONTROL)
        {
            SET_STATUS(keystatus, CONTROL_BIT);
        }
        else if (keyboard_mapping[scancode] == CAPSLOCK)
        {
            if (GET_STATUS(keystatus, CAPSLOCK_BIT))
            {
                UNSET_STATUS(keystatus, CAPSLOCK_BIT);
            }
            else
            {
                SET_STATUS(keystatus, CAPSLOCK_BIT);
            }
        }
    }
    return scancode;
}

char get_key(void)
{
    uint16_t key = 0;

    key = keyboard_handler();
    if (key == 0)
        return 0;
    if (GET_KEY_STATUS(keystatus, SHIFT_BIT) || GET_KEY_STATUS(keystatus, CAPSLOCK_BIT))
    {
        return keyboard_shift_mapping[key];
    }
    return keyboard_mapping[key];
}

static void keyboard()
{
    char key;
    while (true)
    {
        key = get_key();
        if (key != 0)
            last_char = key;
    }
}

//-----------------------------------

char last_char()
{
    char c = last;
    last = 0;
    return c;
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

    while (true)
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
                    set_vga_index(vga_index - 1);
                    i--;
                }
            }
            else if (key == RIGHT_ARROW)
            {
                if (i < strlen(buffer))
                {
                    set_vga_index(vga_index + 1);
                    i++;
                }
            }
            continue;
        }
        else if (key == '\n')
        {
            kputchar(key, VGA_COLOR_WHITE);
            return;
        }
        else if (GET_KEY_STATUS(get_keystatus(), CONTROL_BIT))
        {
            if (key == 'l') {
                memset(buffer, 0, 256);
                clear_screen();
                return;
            }
        }
        else if (key == '\b')
        {
            if (strlen(buffer) > 0 && i > 0)
            {
                clear_previous_char();
                buffer[i - 1] = 0;
                i--;
                move_left_buffer(buffer, buffer_limit, i);
            }
        }
        else {
            k_putchar(key, VGA_COLOR_WHITE);
            move_right_buffer(buffer, buffer_limit, i);
            buffer[i] = key;
            if (strlen(buffer) == buffer_limit) {
                return;
            }
            i++;
        }
    }
}

char init_keyboard()
{
    char buffer[256];
    while (true)
    {
        k_putstr("42>");
        k_memset(buffer, 0, 256);
        get_line(buffer, 256);
    }
}

// https://meepy.medium.com/creating-a-kernel-from-scratch-1a1aa569780f
