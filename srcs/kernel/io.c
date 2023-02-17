#include "io.h"

extern void		outb(size_t port, unsigned char byte)
{
	__asm__ volatile ("outb %0, %w1;"
		 :
		 : "a" (byte), "Nd" (port)
		);
}

extern unsigned char	inb(size_t port)
{
	unsigned char	byte;

	__asm__ volatile ("inb %1, %0"
			: "=a" (byte)
			: "Nd" (port)
	);
	return (byte);
}

