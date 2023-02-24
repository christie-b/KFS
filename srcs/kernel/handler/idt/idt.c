#include "../handler.h"
#include "../../io/io.h"
#include "../../kfunctions/kfunctions.h"

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

t_idt_gate idt[256];
t_idt_gate_ptr idt_gate_ptr;

void set_idt_gate(int n, uint32_t handler, uint32_t selector, uint32_t flags)
{
    idt[n].low_offset = low_16(handler);
    idt[n].high_offset = high_16(handler);

    idt[n].selector = selector; // see GDT
    idt[n].always0 = 0;
    // 0x8E = 1  00 0 1  110
    //        P DPL 0 D Type
    idt[n].flags = flags;
}

void init_idt()
{    
    idt_gate_ptr.base  = (uint32_t)&idt;
    idt_gate_ptr.limit = sizeof(t_idt_gate) * 256 -1;
    k_memset(&idt, 0, sizeof(t_idt_gate) * 256);

    init_interrupt_handlers();
    remap_pic();

    //On set les premieres 32 routines d'interruption dans notre idt (table d'interruption) car elles sont reservees pour les interactions CPU (exception/fault, segfault...)
    set_idt_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
    set_idt_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
    set_idt_gate(2, (uint32_t)isr2 , 0x08, 0x8E);
    set_idt_gate(3, (uint32_t)isr3 , 0x08, 0x8E);
    set_idt_gate(4, (uint32_t)isr4 , 0x08, 0x8E);
    set_idt_gate(5, (uint32_t)isr5 , 0x08, 0x8E);
    set_idt_gate(6, (uint32_t)isr6 , 0x08, 0x8E);
    set_idt_gate(7, (uint32_t)isr7 , 0x08, 0x8E);
    set_idt_gate(8, (uint32_t)isr8 , 0x08, 0x8E);
    set_idt_gate(9, (uint32_t)isr9 , 0x08, 0x8E);
    set_idt_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_idt_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_idt_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_idt_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    set_idt_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    set_idt_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    set_idt_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    set_idt_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    set_idt_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    set_idt_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    set_idt_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    set_idt_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    set_idt_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    set_idt_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    set_idt_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    set_idt_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    set_idt_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    set_idt_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    set_idt_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    set_idt_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    // IRQ interruption request, aussi appelees interruptions hardware
    set_idt_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    set_idt_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    set_idt_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    set_idt_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    set_idt_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    set_idt_gate(37, (uint32_t)irq5, 0x08, 0x8E);
    set_idt_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    set_idt_gate(39, (uint32_t)irq7, 0x08, 0x8E);
    set_idt_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    set_idt_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    set_idt_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    set_idt_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    set_idt_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    set_idt_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    set_idt_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    set_idt_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_flush((uint32_t) &idt_gate_ptr);
}