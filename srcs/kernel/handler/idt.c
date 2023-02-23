#include "handler.h"

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

t_idt_gate idt[256];
t_idt_gate_ptr idt_gate_ptr;

void set_idt_gate(int n, uint32_t handler)
{
    idt[n].low_offset = low_16(handler);
    idt[n].high_offset = high_16(handler);

    idt[n].selector = 0x08; // see GDT
    idt[n].always0 = 0;
    // 0x8E = 1  00 0 1  110
    //        P DPL 0 D Type
    idt[n].flags = 0x8E;
}

void init_idt()
{    
    idt_ptr.limit = sizeof(t_idt_entry) * 256 -1;
    idt_ptr.base  = (uint32)&idt_entries;

    memset(&idt_entries, 0, sizeof(t_idt_entry) * 256);

    init_interrupt_handlers();
    remap_pic();

    //On set les premieres 32 routines d'interruption dans notre idt (table d'interruption) car elles sont reservees pour les interactions CPU (exception/fault, segfault...)
    idt_set_gate(0, (uint32)isr0 , 0x08, 0x8E);
    idt_set_gate(1, (uint32)isr1 , 0x08, 0x8E);
    idt_set_gate(2, (uint32)isr2 , 0x08, 0x8E);
    idt_set_gate(3, (uint32)isr3 , 0x08, 0x8E);
    idt_set_gate(4, (uint32)isr4 , 0x08, 0x8E);
    idt_set_gate(5, (uint32)isr5 , 0x08, 0x8E);
    idt_set_gate(6, (uint32)isr6 , 0x08, 0x8E);
    idt_set_gate(7, (uint32)isr7 , 0x08, 0x8E);
    idt_set_gate(8, (uint32)isr8 , 0x08, 0x8E);
    idt_set_gate(9, (uint32)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (uint32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);

    // IRQ interruption request, aussi appelees interruptions hardware
    idt_set_gate(32, (uint32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32)irq15, 0x08, 0x8E);
}