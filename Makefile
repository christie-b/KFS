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
KERNEL		=	srcs/kernel/kernel.asm
LINKER		=	srcs/linker.ld

FLAGS		=	-fno-builtin -nostdlib -nodefaultlibs -ffreestanding

all: build

build:
	mkdir -p build
	nasm -felf32 ${BOOT} -o build/boot.o
	nasm -felf32 ${KERNEL} -o build/kernel.o
	ld -m elf_i386 -T ${LINKER} -o ${KERNEL_BIN} build/boot.o build/kernel.o


run: build
	qemu-system-i386 -kernel ${KERNEL_BIN} -monitor stdio

clean:
	rm -rf $(KERNEL_BIN) $(KERNEL_ISO)

fclean:
	clear
	rm -rf build/

re: fclean all

.PHONY: all clean fclean re