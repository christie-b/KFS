#ifndef __IO_H__
# define __IO_H__

# include "../kernel.h"

extern void				outb(size_t port, unsigned char byte);
extern unsigned char	inb(size_t port);

#endif