; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot ;Debut de la section multiboot pour le bootloader (programme qui boot les OS sur le PC)
align 4 ; aligne les informations a 32 bits (4 x 8)
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM
 
section .bss ; La section .bss (block starting symbol) declare les variables statiques allouées mais non assignées
align 16 ; alignement a 16 pour respecter la norme System V ABI (sinon crash)
stack_bottom:
resb 16384 ; 16 KiB ; Declaration de 16Kb de stockage non utilisé pour l'instant
stack_top:
 
section .text ; section ou est declaré le code
global _start:function (_start.end - _start) ; voir linker -> entrypoint du programme
_start:
	mov esp, stack_top

	extern kernel_main ; Declaration du symbole externe comme existant dans un autre module (ici kernel.c)
	call kernel_main ; appel de la fonction

	cli ; clear interrupts 
.hang:	hlt ; boucle infinie, si interruption, on jump a la boucle
	jmp .hang
.end: ; fin d'un programme assembleur