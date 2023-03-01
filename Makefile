# *** COLORS *** #
GREY    	=	\033[030m
RED     	=	\033[031m
GREEN   	=	\033[032m
YELLOW  	=	\033[033m
BLUE    	=	\033[034m
MAGENTA 	=	\033[035m
CYAN		=	\033[036m
BOLD		=	\033[1m
RESET   	=	\033[0m


KERNEL_BIN	=	build/our_kfs.bin
KERNEL_ISO	=	build/our_kfs.iso

BOOT		=	srcs/boot/boot.asm
KERNEL		=	srcs/kernel/kernel.c
LINKER		=	srcs/linker.ld

FLAGS		=	-fno-builtin -nostdlib -nodefaultlibs -ffreestanding -fno-exceptions -fno-stack-protector # -fno-rtti is for C++

all: build

build:
	mkdir -p build
	nasm -felf32 ${BOOT} -o build/boot.o
	# nasm -felf32 ${KERNEL} -o build/kernel.o
	# i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 ${FLAGS} -c ${KERNEL} -o build/kernel.o
	gcc -m32 ${FLAGS} -c srcs/kernel/cursor/cursor.c -o build/cursor.o
	gcc -m32 ${FLAGS} -c srcs/kernel/handler/handler.c -o build/handler.o
	gcc -m32 ${FLAGS} -c srcs/kernel/handler/idt/idt.c -o build/idt.o
	gcc -m32 ${FLAGS} -c srcs/kernel/handler/irq/irq.c -o build/irq.o
	gcc -m32 ${FLAGS} -c srcs/kernel/handler/isr/isr.c -o build/isr.o
	gcc -m32 ${FLAGS} -c srcs/kernel/handler/gdt/gdt.c -o build/gdt.o
	nasm -felf32 srcs/kernel/handler/gdt/gdt_flush.asm -o build/gdt_flush.o
	nasm -felf32 srcs/kernel/handler/idt/idt_flush.asm -o build/idt_flush.o
	nasm -felf32 srcs/kernel/handler/irq/irq.asm -o build/irqasm.o
	nasm -felf32 srcs/kernel/handler/isr/isr.asm -o build/israsm.o
	gcc -m32 ${FLAGS} -c srcs/kernel/io/io.c -o build/io.o
	gcc -m32 ${FLAGS} -c srcs/kernel/keyboard/keyboard.c -o build/keyboard.o
	gcc -m32 ${FLAGS} -c srcs/kernel/kfunctions/kfunctions.c -o build/kfunctions.o
	gcc -m32 ${FLAGS} -c srcs/kernel/shell/shell.c -o build/shell.o
	gcc -m32 ${FLAGS} -c srcs/kernel/vga/vga.c -o build/vga.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_BIN} build/boot.o build/kernel.o build/cursor.o build/idt_flush.o build/gdt_flush.o build/handler.o build/gdt.o build/idt.o build/irq.o build/isr.o build/irqasm.o build/israsm.o build/io.o build/keyboard.o build/kfunctions.o build/shell.o build/vga.o -nostdlib
	# ld -m elf_i386 -T ${LINKER} -o ${KERNEL_BIN} build/boot.o build/kernel.o build/keyboard.o -nostdlib


run: build
	qemu-system-i386 -kernel ${KERNEL_BIN} -monitor stdio

iso: build
	mkdir -p build/iso/boot/grub
	cp srcs/grub.cfg build/iso/boot/grub
	cp ${KERNEL_BIN} build/iso/boot
	grub-mkrescue -o ${KERNEL_ISO} build/iso

run-iso: iso
	qemu-system-i386 -cdrom ${KERNEL_ISO}


clean:
	rm -rf $(KERNEL_BIN) $(KERNEL_ISO)

fclean:
	clear
	rm -rf build/

re: fclean all

copy:
	@ docker cp . kfs:/workspace
	@ docker exec -w /workspace -it kfs /bin/bash
	# @ docker exec -it kfs /bin/bash

.PHONY: all clean fclean re