#ifndef SHELL_H
#define SHELL_H

# include "../kernel.h"

void            init_shell();
void            get_line(char *buffer, unsigned int buffer_limit);
static void     move_left_buffer(char *buffer, int size, int index);
static void     move_right_buffer(char *buffer, int size, int index);

#endif