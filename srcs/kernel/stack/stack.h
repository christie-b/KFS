#ifndef STACK_H
#define STACK_H
#include <stdint.h>
# include "../kfunctions/kfunctions.h"
# include "../vga/vga.h"

// %%ebp: first percent sign is the operand indicator, 
// and the second percent sign is an escape character that tells the compiler to treat the third character as a literal character ("ebp")
// "%0" is a placeholder for the output operand of the assembly instruction, which is the variable "x". The "=r" syntax means that the compiler can use any register to hold the value of "x".
// "::" specifies the clobber list, which tells the compiler which registers are being modified by the assembly code. In this case, there are no clobbered registers, :: tells the compiler that the code does not modify any registers or memory locations.
#define GET_EBP(x) asm volatile("mov %%ebp, %0" : "=r"(x) ::)
#define GET_ESP(x) asm volatile("mov %%esp, %0" : "=r"(x) ::)

void print_memory(const uintptr_t addr, size_t size);
void kdump(uint32_t addr, int limit);

#endif
