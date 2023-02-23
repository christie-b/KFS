#include "handler.h"

void isr_handler(t_registers regs)
{
    if (interrupt_handlers[regs.int_no] != 0)
    {
        t_interrupt_handler_func_ptr handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    switch (regs.int_no)
    {
        case 0:
            k_print(KERR "Division by Zero\n");
            break;
        case 1:
            k_print(KERR "Debug\n");
            break;
        case 2:
            k_print(KERR "Non Maskable Interrupt\n");
            break;
        case 3:
            k_print(KERR "Breakpoint\n");
            break;
        case 4:
            k_print(KERR "Overflow\n");
            break;
        case 5:
            k_print(KERR "Bound Range Exceeded\n");
            break;
        case 6:
            k_print(KERR "Invalid Opcode\n");
            break;
        case 7:
            k_print(KERR "Device Not Available\n");
            break;
        case 8:
            k_print(KERR "Double Fault\n");
            break;
        case 10:
            k_print(KERR "Invalid TSS\n");
            break;
        case 11:
            k_print(KERR "Segment Not Present\n");
            break;
        case 12:
            k_print(KERR "Stack-Segment Fault\n");
            break;
        case 13:
            k_print(KERR "General Protection Fault\n");
            break;
        case 14:
            k_print(KERR "Page Fault\n");
            break;
        default:
            k_print(KERR "ISR code = %d\n", regs.int_no);
            break;
    }
}