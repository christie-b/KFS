#ifndef KEYBOARD_H
#define KEYBOARD_H 

# include "../kernel.h"

# define RELEASED(keycode) keycode & 0x80
# define GET_STATUS(status, key) (status >> key) & 1
# define SET_STATUS(status, key) status ^= (-1 ^ status) & (1 << key)
# define UNSET_STATUS(status, key) status ^= (0 ^ status) & (1 << key)
# define GET_RELEASED_KEY(keycode) keycode ^ 0x80

# define SHIFT_BIT              1
# define SHIFT                  -1
# define CONTROL_BIT            2
# define CONTROL                -2
# define CAPSLOCK_BIT           3
# define CAPSLOCK               -3
# define LEFT_ARROW             -10
# define RIGHT_ARROW            -11

char            last_char();
char            keystatus_getter();
void            init_keyboard();

#endif

//https://forum.osdev.org/viewtopic.php?f=1&t=28437#:~:text=To%20get%20input%20from%20the,to%20terminate%20the%20interrupt%20cleanly.
//https://wiki.osdev.org/Text_Mode_Cursor
//https://wiki.osdev.org/Creating_A_Shell
