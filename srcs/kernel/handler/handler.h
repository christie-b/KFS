#ifndef HANDLER_H
#define HANDLER_H

# include "../kernel.h"

# define IRQ1 33

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


typedef struct __attribute__((packed)) idt_gate {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} t_idt_gate;

typedef struct __attribute__((packed)) idt_gate_ptr {
    uint16_t limit;
    uint32_t base;
} t_idt_gate_ptr;

typedef struct registers {
    // data segment selector
    uint32_t ds;
    // general purpose registers pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // pushed by isr procedure
    uint32_t int_no, err_code;
    // pushed by CPU automatically
    uint32_t eip, cs, eflags, useresp, ss;
} t_registers;

typedef void (*t_interrupt_handler_func_ptr)(t_registers);

// HANDLER
void enable_interrupts();
void disable_interrupts();
void register_interrupt_handler(uint8_t n, t_interrupt_handler_func_ptr handler);
t_interrupt_handler_func_ptr get_interrupt_handler(uint8_t n);
void init_interrupt_handlers();

// IRQ
void remap_pic();
void irq_handler(t_registers regs);

// ISR
void isr_handler(t_registers regs);

// IDT
void set_idt_gate(int n, uint32_t handler);
void init_idt();

#endif
//https://wiki.osdev.org/What_order_should_I_make_things_in
//https://wiki.osdev.org/Interrupt_Descriptor_Table
//https://wiki.osdev.org/Interrupts
//https://wiki.osdev.org/Interrupt_Service_Routines
//https://wiki.osdev.org/Exceptions
//https://github.com/stevej/osdev/blob/master/kernel/cpu/irq.c
//https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh