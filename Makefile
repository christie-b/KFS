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

BOOT		=	srcs/boot/boot.s
KERNEL		=	srcs/kernel/kernel.c
LINKER		=	srcs/linker.ld

FLAGS		=	-fno-builtin -nostdlib -nodefaultlibs -ffreestanding

all: build

build:
	mkdir -p build
	nasm -f elf32 ${BOOT} -o build/boot.o
	echo "HERE"
	# i686-elf-as ${BOOT} -o build/boot.o
	# gcc -m32 ${FLAGS} -c ${KERNEL} -o build/kernel.o
	i686-elf-gcc -c ${KERNEL} -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	# ld -m elf_i386 -T ${LINKER} -o ${KERNEL_BIN} build/boot.o build/kernel.o
	i686-elf-gcc -T ${LINKER} -o ${KERNEL_BIN} -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc


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

.PHONY: all clean fclean re