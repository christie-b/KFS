# include "stack.h"

void	*memset(char *str, char c, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
    {
		str[i] = c;
        i++;
    }
	return str;
}

// Converts a single byte into a two-character hexadecimal string
void hex_to_str(unsigned int addr, char *str, int size)
{
    int		len;
    char    base_str[16] = "0123456789abcdef";

	len = size - 1;
    memset(str, '0', size);
    str[len] = '\0';
	while (addr != 0)
	{
		str[--len] = base_str[addr % 16];
		addr = addr / 16;
	}
}



int isprint(int c)
{
    return (c >= 32 && c <= 126);
}


void print_memory(const uintptr_t addr, size_t size)
{
    const unsigned char *ptr = (unsigned char*)addr;
    char buf[50];
    int pos = 0;
    char str_addr[9];

    for (size_t i = 0; i < size; ++i, ++ptr)
    {
        if (i % 16 == 0)
        {
            pos = 0;
            // prints the address of the current byte in hexadecimal format
            pos += (int)k_itoa_x((uint32_t)ptr, buf + pos, 16);
            k_putstr("0x", VGA_COLOR_WHITE);
            k_putstr(buf, VGA_COLOR_WHITE);
            k_putchar(' ', VGA_COLOR_WHITE);
        }
        // prints the byte in hexadecimal format
        hex_to_str(*(ptr), str_addr, 3);
        k_print("%s ", str_addr);
        pos += (int)k_itoa_x(*ptr, buf + pos, 16);
        // after printing every 16 bytes, print a space
        if ((i + 1) % 16 == 0)
        {
            k_putchar(' ', VGA_COLOR_WHITE);
            for (int j = 0; j < 16; j++)
            {
                // print the character, if not printable, print a '.'
                if (isprint(*(ptr - 15 + j)))
                {
                    k_putchar(*(ptr - 15 + j), VGA_COLOR_WHITE);
                }
                else
                {
                    k_putchar('.', VGA_COLOR_WHITE);
                }
            }
            k_putchar('\n', VGA_COLOR_WHITE);
        }
    }

// If the size of the memory contents is not a multiple of 16,
// print the remaining bytes with padding spaces to align the output.
// i.e. last line
    if (size % 16 != 0)
    {
        for (size_t i = 0; i < 16 - (size % 16); i++)
        {
            k_putstr("   ", VGA_COLOR_WHITE);
        }

        k_putchar(' ', VGA_COLOR_WHITE);
        for (size_t i = 0; i < size % 16; i++)
        {
            if (isprint(*(ptr - (size % 16) + i)))
            {
                k_putchar(*(ptr - (size % 16) + i), VGA_COLOR_WHITE);
            }
            else
            {
                k_putchar('.', VGA_COLOR_WHITE);
            }
        }
        k_putchar('\n', VGA_COLOR_WHITE);
    }
}
