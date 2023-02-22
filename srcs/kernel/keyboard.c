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

unsigned char get_scancode()
{
    unsigned char inputdata;
    inputdata = inb(0x60);
    return inputdata;
}

void keyboard_handler()
{
    unsigned char scancode;

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
    return ;
}

/*
char get_char(void)
{
    uint16_t      keycode = 0;

    keycode = keyboard_handler();
    if (keycode == 0)
        return 0;
    if (GET_KEY_STATUS(keystatus, SHIFT_BIT) || GET_KEY_STATUS(keystatus, CAPSLOCK_BIT))
    {
            return keyboard_shift_mapping[keycode];
    }
    else
    {
        return keyboard_mapping[keycode];
    }
}
// https://meepy.medium.com/creating-a-kernel-from-scratch-1a1aa569780f
*/