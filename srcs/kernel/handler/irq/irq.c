#include "../handler.h"
#include "../../io/io.h"
#include "../../kfunctions/kfunctions.h"

// le pic est responsable des interruptions liees au hardware, on le remap car de base,
// elles sont set aux 8 premieres gate de la table d'interruption et ca rentre en conflit avec les gates reservees par le cpu
void remap_pic()
{
    // internal ISRs
    // ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW2
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // ICW3
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // ICW4
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    // OCW1
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq_handler(t_registers regs)
{
    /* Send EOI (end of interrupt) signal to the PICs */
    if (regs.int_no >= 40)
    {
        /* reset signal to slave */
        outb(0xA0, 0x20);
    }
    /* reset signal to master */
    outb(0x20, 0x20);

    if (get_interrupt_handler(regs.int_no) != 0)
    {
        t_interrupt_handler_func_ptr handler = get_interrupt_handler(regs.int_no);
        handler(regs);
    }
} 