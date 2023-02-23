#ifndef HANDLER_H
#define HANDLER_H

# include "../kernel.h"

# define IRQ1 33

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


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
void set_idt_gate(int n, uint32_t handler, uint32_t selector, uint32_t flags);
void init_idt();

#endif
//https://wiki.osdev.org/What_order_should_I_make_things_in
//https://wiki.osdev.org/Interrupt_Descriptor_Table
//https://wiki.osdev.org/Interrupts
//https://wiki.osdev.org/Interrupt_Service_Routines
//https://wiki.osdev.org/Exceptions
//https://github.com/stevej/osdev/blob/master/kernel/cpu/irq.c
//https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh