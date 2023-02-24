#include "kernel.h"
#include "handler/handler.h"
#include "keyboard/keyboard.h"
#include "shell/shell.h"
#include "vga/vga.h"

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	clear_screen();
	init_gdt();
	init_idt();
	asm volatile ("sti");
	init_keyboard();
	init_shell();
}
