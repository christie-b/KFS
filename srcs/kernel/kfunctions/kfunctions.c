#include "kfunctions.h"

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
    if (c == '\n')
    {
        newline();
    }
    else
    {
        move_right();
        terminal_buffer[vga_index] = (unsigned short) c  | (unsigned short) colour << 8;;
        vga_index++;
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
            else if (opt[i] == 'x') 
            {
                k_memset(tmp_addr, 0, sizeof(tmp_addr));
                //hex_to_str(*args++, tmp_addr, sizeof(tmp_addr));
                k_putstr(tmp_addr, VGA_COLOR_WHITE);
            }
            else if (opt[i] == 'p')
            {
                k_memset(tmp_addr, 0, sizeof(tmp_addr));
                //hex_to_str(*args++, tmp_addr, sizeof(tmp_addr));
                k_putstr("0x", VGA_COLOR_WHITE);
                k_putstr(tmp_addr, VGA_COLOR_WHITE);
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