#include "kernel.h"
#include "handler/handler.h"
#include "keyboard/keyboard.h"
#include "shell/shell.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/*
// Set la couleur de la police (fg) et du background (bg) dans un seul int8
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
// Set le character (8 bits) et la couleur precedement determinee (8 bit) dans un seul int16
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

 // Declaration des variables globales necessaires
 // (numero de la rangee actuelle, numero de la colonne actuelle, couleur du terminal et buffer de tout ce qui est entré dans le terminal
 //-> sur 16 bit pour stocker la couleur fg, bg et le char) 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
// uint16_t* terminal_buffer;
size_t index;

//Init le terminal, set les 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000; // Aucune idee pourquoi ca c'est la
	// J'ai trouvé ca sur internet 
	
	0xb800 is usually mapped to text mode video memory.
	Writing to this location overwrites what is displayed on screen
	(Assuming text mode and assuming the mapped address is not changed)
	

	//Ensuite on remplit le buffer d'espaces (chacun des 80 caracteres des 25 lignes disponibles)
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
// Fonction non appelee (a voir ce que ca fait si on la supprime)
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x; // Calcule la position de l'entree dans le buffer (nombre de ligne * nombre de charactere par ligne + position actuelle dans la ligne)
	terminal_buffer[index] = vga_entry(c, color); // Set l'entree dans le buffer
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	// On augmente la colonne et ensuite si on est a 80 alors alors on repasse au debut et on passe a une autre ligne
	// et si on est au nombre max de ligne alors on reset les lignes  
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
			// Je suppose que cela veut dire que si on depasse cette
			//ligne on va alors reecrire par dessus le premier de la premiere ligne? 
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
// Passe plat qu'on pourrait enelever en passant directement terminal write comme commenté si dessous
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
*/
 
void kernel_main(void) 
{
	clear_screen();
	init_idt();
	init_keyboard();
	init_shell();
}
