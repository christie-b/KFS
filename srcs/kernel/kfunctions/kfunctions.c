#include "kfunctions.h"
#include "../vga/vga.h"

int		k_strcmp(const char *s1, const char *s2)
{
	int i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

unsigned int k_strlen(const char *str)
{
	unsigned int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

unsigned int k_intlen(int n)
{
	int		i;

	i = 1;
    if (n < 0)
    {
        n = -n;
        i++;
    }
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	*k_memset(void *buffer, int ch, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
    {
		((char *)(buffer))[i] = ch;
        i++;
    }
    return buffer;
}

#include <stddef.h>

char *k_itoa_x(int num, char *str, int base)
{
    // Array of characters to use for each digit in the base
    char digits[] = "0123456789ABCDEF";

    // Keep track of whether the number is negative
    int is_negative = 0;

    // Handle negative numbers for bases other than 10
    if (num < 0 && base != 10) {
        num = -num;
        is_negative = 1;
    }

    // Handle negative numbers for base 10
    if (num < 0 && base == 10) {
        num = -num;
        is_negative = 1;
    }

    // Calculate the digits of the number in the given base
    size_t i = 0;
    do {
        str[i++] = digits[num % base];
        num /= base;
    } while (num > 0);

    // Add a minus sign if the number is negative
    if (is_negative) {
        str[i++] = '-';
    }

    // Terminate the string
    str[i] = '\0';

    // Reverse the string
    size_t j = 0;
    size_t len = i;
    for (j = 0; j < len / 2; j++) {
        char tmp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = tmp;
    }

    return str;
}


    void k_itoa(int n, char *str)
    {
    	int		nb;
    	int		i;
        int     len;
        
        nb = n;
        len = k_intlen(n);
        k_memset(str, 0, len + 1);
        if (nb < 0) {
            nb = -nb;
        }
    	i = len - 1;
        if (nb == 0) {
            str[i] = '0';
            return;
        }
    	while (nb != 0)
    	{
    		str[i--] = (nb % 10) + '0';
    		nb = nb / 10;
    	}
    	if (n < 0)
    		str[i] = '-';
    }

void k_putnbr(int n, unsigned char color)
{
    char    str[k_intlen(n) + 1];

    k_itoa(n, str);
    k_putstr(str, color);
}

void k_putchar(char c, unsigned char colour)
{
    if (vga_index + 1 > VGA_COUNT)
        scroll_up();
    if (c == '\n')
    {
        newline();
    }
    else
    {
        move_right();
        terminal_buffer[vga_index] = (unsigned short) c  | (unsigned short) colour << 8;;
        move_cursor_right(1);
    }
}


void k_putstr(char *str, unsigned char colour)
{
    int i = 0;
    while (str[i])
    {
        k_putchar(str[i], colour);
        i++;
    }
}

int k_hexlen(int num) {
    int len = 0;
    while (num != 0) {
        len++;
        num /= 16;
    }
    return len;
}

void k_puthex(int num, unsigned char colour) {
    char buf[9];
    int i = 0;
    while (num != 0) {
        int digit = num % 16;
        buf[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        num /= 16;
    }
    while (i < 8) {
        buf[i++] = '0';
    }
    for (int j = 7; j >= 0; j--) {
        k_putchar(buf[j], colour);
    }
}


void k_print(char *str, ...)
{
    int         *args = (int *)(&str);
    char        *opt = (char *)(*args++);
    int         i = 0;
    uint8_t     padding = 0;
    char        tmp_addr[9];

    while (opt[i])
    {
        padding = 0;
        if (opt[i] == '%')
        {
            i++;
            if (opt[i] == '0')
            {
                i++;
                padding = opt[i] - '0';
                i++;
            }
            if (opt[i] == 'c')
            {
                k_putchar(*args++, VGA_COLOR_WHITE);
            }
            else if (opt[i] == 's')
            {
                k_putstr(*((char **)args++), VGA_COLOR_WHITE);
            }
            else if (opt[i] == 'd')
            {
                if (padding > 0)
                {
                    while (padding - k_intlen(*args))
                    {
                        k_putchar('0', VGA_COLOR_WHITE);
                        padding--;
                    }
                }
                k_putnbr(*args++, VGA_COLOR_WHITE);
            }
            else if (opt[i] == 'x')
            {
                if (padding > 0)
                {
                    while (padding - k_hexlen(*args))
                    {
                        k_putchar('0', VGA_COLOR_WHITE);
                        padding--;
                    }
                }
                k_puthex(*args++, VGA_COLOR_WHITE);
            }
            else
            {
                k_putchar('%', VGA_COLOR_WHITE);
                k_putchar(opt[i], VGA_COLOR_WHITE);
            }
        }
        else
        {
            k_putchar(opt[i], VGA_COLOR_WHITE);
        }
        i++;
    }
}

//git clone https://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@github.com/christie-b/KFS.git