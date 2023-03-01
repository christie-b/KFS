#include "handler.h"
#include "../io/io.h"
#include "../kfunctions/kfunctions.h"

t_interrupt_handler_func_ptr interrupt_handlers[256];

void init_interrupt_handlers(void)
{
    k_memset(&interrupt_handlers, 0, sizeof(t_interrupt_handler_func_ptr) * 256);
}

t_interrupt_handler_func_ptr get_interrupt_handler(uint8_t n)
{
    return interrupt_handlers[n];
}

void register_interrupt_handler(uint8_t n, t_interrupt_handler_func_ptr handler)
{
    interrupt_handlers[n] = handler;
} 

void disable_interrupts()
{
    asm volatile("cli");
}

void enable_interrupts()
{
    asm volatile("sti");
}