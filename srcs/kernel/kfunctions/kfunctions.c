#include "kfunctions.h"

unsigned int k_strlen(const char *str)
{
	unsigned int i;

	i = 0;
	while (str && str[i])
		i++;
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
                k_putchar(*args++);
            }
            else if (opt[i] == 's')
            {
                k_putstr(*((char **)args++));
            }
            else if (opt[i] == 'x') 
            {
                k_memset(tmp_addr, 0, sizeof(tmp_addr));
                hex_to_str(*args++, tmp_addr, sizeof(tmp_addr));
                k_putstr(tmp_addr);
            }
            else if (opt[i] == 'p')
            {
                k_memset(tmp_addr, 0, sizeof(tmp_addr));
                hex_to_str(*args++, tmp_addr, sizeof(tmp_addr));
                k_putstr("0x");
                k_putstr(tmp_addr);
            }
            else if (opt[i] == 'd')
            {
                if (padding > 0)
                {
                    while (padding - intlen(*args))
                    {
                        k_putchar('0');
                        padding--;
                    }
                }
                k_putnbr(*args++);
            }
            else
            {
                k_putchar('%');
                k_putchar(opt[i]);
            }
        }
        else
        {
            k_putchar(opt[i]);
        }
        i++;
    }
}

//git clone https://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@github.com/christie-b/KFS.git