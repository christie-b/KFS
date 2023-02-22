#ifndef KFONCTIONS_H
# define KFONCTIONS_H

#include "source.h"
#include "io.h"

void k_putstr(char *str);
void k_putchar(char c);
unsigned int k_strlen(const char *str);
void	*k_memset(void *buffer, int char, unsigned int len);

#endif