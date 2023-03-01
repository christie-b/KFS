#ifndef KFONCTIONS_H
#define KFONCTIONS_H

# include "../kernel.h"

unsigned int    k_strlen(const char *str);
void	        *k_memset(void *buffer, int ch, unsigned int len);
void            k_putchar(char c, unsigned char colour);
void            k_putstr(char *str, unsigned char colour);
void            k_print(char *str, ...);
int		        k_strcmp(const char *s1, const char *s2);

#endif