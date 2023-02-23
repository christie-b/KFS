#include "keyboard.h"
#include "../io/io.h"
#include "../handler/handler.h"

char last = 0;
int clicked = 0;
int canSend = 0;
char keystatus = 0;

static char keyboard_mapping[128] =
{
	0, 0, '&', 0, '"', '\'', '(', 0, 0, '!', 0, 0, ')', '-', '\b', 0, 'a', 'z',
    'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0, 'q', 's', 'd',
    'f', 'g', 'h', 'j', 'k', 'l', 'm', 0, '<', 0, '`', 'w', 'x', 'c', 'v', 'b',
    'n', ',', ';', ':', '=', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', '6',
	0, 0, 0, 0, 0
};

static char keyboard_shift_mapping[128] =
{
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, '_', '\b', 0,
    'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, '*', '\n', 0, 'Q', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', '>', 0, 0, 'W', 'X', 'C', 'V',
    'B', 'N', '?', '.', '/', '+', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    '6', 0, 0, 0, 0, 0
};

char keystatus_getter()
{
    return keystatus;
}

char last_char()
{
    char c = last;
    last = 0;
    return c;
}

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
        return 0;
    }
    else // Key is pressed
    {
        outb(0x60, 0);
        // Between 0 and 128 
        if (scancode > 128)
        {
            return 0;
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

char get_key()
{
    uint16_t key = 0;

    key = keyboard_handler();
    if (key == 0)
        return 0;
    if (GET_STATUS(keystatus, SHIFT_BIT) || GET_STATUS(keystatus, CAPSLOCK_BIT))
    {
        return keyboard_shift_mapping[key];
    }
    return keyboard_mapping[key];
}

static void keyboard(t_registers regs)
{
    (void)regs;
    char key;
    key = get_key();
    if (key != 0)
        last = key;
}


void init_keyboard()
{
    register_interrupt_handler(IRQ1, &keyboard);
}

// https://meepy.medium.com/creating-a-kernel-from-scratch-1a1aa569780f
// https://stackoverflow.com/questions/2746817/what-does-the-0x80-code-mean-when-referring-to-keyboard-controls
//https://forum.osdev.org/viewtopic.php?f=1&t=28437#:~:text=To%20get%20input%20from%20the,to%20terminate%20the%20interrupt%20cleanly.
