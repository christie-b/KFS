#ifndef __IO_H__
# define __IO_H__

# include "../kernel.h"

extern void				outb(size_t port, uint8_t byte);
extern void				outw(size_t port, uint16_t byte);
extern unsigned char	inb(size_t port);

#endif