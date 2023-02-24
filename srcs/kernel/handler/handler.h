#ifndef HANDLER_H
#define HANDLER_H

//https://wiki.osdev.org/What_order_should_I_make_things_in
//https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh

# include "../kernel.h"

#pragma region IDT
//https://wiki.osdev.org/Interrupt_Descriptor_Table
typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed))t_idt_gate;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) t_idt_gate_ptr;

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

extern void idt_flush(uint32_t idt_ptr);
void set_idt_gate(int n, uint32_t handler, uint32_t selector, uint32_t flags);
void init_idt();
#pragma endregion IDT

#pragma region HANDLER
void enable_interrupts();
void disable_interrupts();
void register_interrupt_handler(uint8_t n, t_interrupt_handler_func_ptr handler);
t_interrupt_handler_func_ptr get_interrupt_handler(uint8_t n);
void init_interrupt_handlers();
#pragma endregion HANDLER

#pragma region ISR
//https://wiki.osdev.org/Interrupt_Service_Routines
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

void isr_handler(t_registers regs);
#pragma endregion ISR

#pragma region IRQ
//https://wiki.osdev.org/Interrupts
//https://github.com/stevej/osdev/blob/master/kernel/cpu/irq.c
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

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

void remap_pic();
void irq_handler(t_registers regs);
#pragma endregion IRQ

#pragma region GDT
//https://wiki.osdev.org/Global_Descriptor_Table
//https://wiki.osdev.org/GDT_Tutorial
//https://wiki.osdev.org/Exceptions
#define GDT_ADDRESS 0x00000800
#define GDT_ENTRIES 7

#define SEG_DESCTYPE(x) ((x) << 0x04)           /* Descriptor type (0 for system, 1 for code/data) */
#define SEG_PRES(x) ((x) << 0x07)               /* Present */
#define SEG_SAVL(x) ((x) << 0x0C)               /* Available for system use */
#define SEG_LONG(x) ((x) << 0x0D)               /* Long mode */
#define SEG_SIZE(x) ((x) << 0x0E)               /* Size (0 for 16-bit, 1 for 32) */
#define SEG_GRAN(x) ((x) << 0x0F)               /* Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB) */
#define SEG_PRIV(x) (((x) &  0x03) << 0x05)     /* Set privilege level (0 - 3) */
 
#define SEG_DATA_RD        0x00     /* Read-Only */
#define SEG_DATA_RDA       0x01     /* Read-Only, accessed */
#define SEG_DATA_RDWR      0x02     /* Read/Write */
#define SEG_DATA_RDWRA     0x03     /* Read/Write, accessed */
#define SEG_DATA_RDEXPD    0x04     /* Read-Only, expand-down */
#define SEG_DATA_RDEXPDA   0x05     /* Read-Only, expand-down, accessed */
#define SEG_DATA_RDWREXPD  0x06     /* Read/Write, expand-down */
#define SEG_DATA_RDWREXPDA 0x07     /* Read/Write, expand-down, accessed */
#define SEG_CODE_EX        0x08     /* Execute-Only */
#define SEG_CODE_EXA       0x09     /* Execute-Only, accessed */
#define SEG_CODE_EXRD      0x0A     /* Execute/Read */
#define SEG_CODE_EXRDA     0x0B     /* Execute/Read, accessed */
#define SEG_CODE_EXC       0x0C     /* Execute-Only, conforming */
#define SEG_CODE_EXCA      0x0D     /* Execute-Only, conforming, accessed */
#define SEG_CODE_EXRDC     0x0E     /* Execute/Read, conforming */
#define SEG_CODE_EXRDCA    0x0F     /* Execute/Read, conforming, accessed */
 
/* 0x9A */
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
/* 0x92 */
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

/* 0x96 */
#define GDT_STACK_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWREXPD

/* 0xFA */
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD

/* 0xF2 */
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

/* 0xF6 */
#define GDT_STACK_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWREXPD

typedef struct  __attribute__((packed)) gdt_entry
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
}  t_gdt_entry;

typedef struct  __attribute__((packed)) gdt_ptr
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} t_gdt_ptr;

extern void gdt_flush(uint32_t gdt_ptr);

void init_gdt();
#pragma endregion GDT

#endif