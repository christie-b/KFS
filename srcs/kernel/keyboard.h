#ifndef KEYBOARD_H
#define KEYBOARD_H 

# define RELEASED(keycode) keycode & 0x80
# define GET_STATUS(status, key) (status >> key) & 1
# define SET_STATUS(status, key) status ^= (-1 ^ status) & (1 << key)
# define UNSET_STATUS(status, key) status ^= (0 ^ status) & (1 << key)
# define GET_RELEASED_KEY(keycode) keycode ^ 0x80

# define SHIFT_BIT              1
# define SHIFT                 -1
# define CONTROL_BIT            2
# define CONTROL               -2
# define CAPSLOCK_BIT           3
# define CAPSLOCK               -3

unsigned char get_scancode();
void keyboard_handler();


#endif