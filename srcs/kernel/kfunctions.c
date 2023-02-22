void k_putchar(char c)
{
    if (c == '\n')
    {
        newline();
    }
    else
    {
        move_right();
        terminal_buffer[vga_index] = (unsigned short) c;
        vga_index++;
    }
}

void k_putstr(char *str)
{
    int i = 0;
    while (str[i])
    {
        k_putchar(str[i]);
        i++;
    }
}

void	*k_memset(void *buffer, int char, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
    {
		((char *)(buffer))[i] = char;
        i++;
    }
    return buffer;
}
unsigned int k_strlen(const char *str)
{
	unsigned int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
//git clone https://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@github.com/christie-b/KFS.git