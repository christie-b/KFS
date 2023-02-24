#include "../handler.h"
#include "../../io/io.h"
#include "../../kfunctions/kfunctions.h"

extern t_interrupt_handler_func_ptr interrupt_handlers[256];

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
            k_print("Division by Zero\n");
            break;
        case 1:
            k_print("Debug\n");
            break;
        case 2:
            k_print("Non Maskable Interrupt\n");
            break;
        case 3:
            k_print("Breakpoint\n");
            break;
        case 4:
            k_print("Overflow\n");
            break;
        case 5:
            k_print("Bound Range Exceeded\n");
            break;
        case 6:
            k_print("Invalid Opcode\n");
            break;
        case 7:
            k_print("Device Not Available\n");
            break;
        case 8:
            k_print("Double Fault\n");
            break;
        case 10:
            k_print("Invalid TSS\n");
            break;
        case 11:
            k_print("Segment Not Present\n");
            break;
        case 12:
            k_print("Stack-Segment Fault\n");
            break;
        case 13:
            k_print("General Protection Fault\n");
            break;
        case 14:
            k_print("Page Fault\n");
            break;
        default:
            k_print("ISR code = %d\n", regs.int_no);
            break;
    }
}