#include "io.h"

// The "inb" command performs an input (read) operation on the given I/O port and print the result.
// The "outb" command performs an output (write) operation to the given I/O port, sending the given data.

// Inline assemby.
// Sends a 8-bit value on a I/O location.
// a modifier enforces val to be placed in the eax register before the asm command is issued
// Nd allows for one-byte constant values to be assembled as constants, 
// freeing the edx register for other cases. 
extern void		outb(size_t port, unsigned char byte)
{
	__asm__ volatile ("outb %0, %w1;"
		 :
		 : "a" (byte), "Nd" (port)
		);
}

// Receives a byte
extern unsigned char	inb(size_t port)
{
	unsigned char	byte;

	__asm__ volatile ("inb %1, %0"
			: "=a" (byte) // "=a" constraint means that al/ax/eax will be copied to ret as output,
			: "Nd" (port) // N ->Unsigned 8-bit integer constant  dx -> d register
	);
	return (byte);
}

// https://wiki.osdev.org/Inline_Assembly/Examples