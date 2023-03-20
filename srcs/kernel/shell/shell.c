#include "shell.h"
#include "../keyboard/keyboard.h"
#include "../kfunctions/kfunctions.h"
#include "../vga/vga.h"
#include "../stack/stack.h"
#include "../io/io.h"

static void move_right_buffer(char *buffer, int size, int index)
{
    while (size > index)
    {
        buffer[size] = 0;
        buffer[size] = buffer[size - 1];
        size--;
    }

}

static void move_left_buffer(char *buffer, int size, int index)
{
    while (index < size)
    {
        buffer[index] = 0;
        buffer[index] = buffer[index + 1];
        index++;
    }

}

void get_line(char *buffer, unsigned int buffer_limit)
{
    char                key = 0;
    unsigned int        i = 0;

    while (1)
    {
        key = last_char();
        if (key == 0)
        {
            continue;
        }
        else if (key < 0)
        {
            if (key == LEFT_ARROW)
            {
                if (i > 0)
                {
                    move_cursor_left(1);
                    i--;
                }
            }
            else if (key == RIGHT_ARROW)
            {
                if (i < k_strlen(buffer))
                {
                    move_cursor_right(1);
                    i++;
                }
            }
            continue;
        }
        if (key == '\n')
        {
            k_putchar(key, VGA_COLOR_WHITE);
            return;
        }
        if (GET_STATUS(keystatus_getter(), CONTROL_BIT))
        {
            if (key == 'l')
            {
                k_memset(buffer, 0, 256);
                clear_screen();
                return;
            }
        }
        if (key == '\b')
        {
            if (k_strlen(buffer) > 0 && i > 0)
            {
                clear_previous_char();
                buffer[i - 1] = 0;
                i--;
                move_left_buffer(buffer, buffer_limit, i);
            }
        }
        else
        {
            k_putchar(key, VGA_COLOR_WHITE);
            move_right_buffer(buffer, buffer_limit, i);
            buffer[i] = key;
            if (k_strlen(buffer) == buffer_limit)
            {
                return;
            }
            i++;
        }
    }
}

// Sends the 0xFE command to the keyboard controller, which is the command to initiate a system reset.
// Then, it executes the cli instruction to disable interrupts and the hlt instruction to halt the CPU until the reset occurs.
void reboot(void)
{
    uint8_t good = 0x02;
    // loop that waits until the keyboard controller is ready to receive data
    while (good & 0x02)
    {
        // inb() reads the value of the status port of the keyboard controller (which is located at port 0x64) 
        good = inb(0x64); 
    }
    // outb() function writes the value 0xFE to port 0x64, which is the keyboard controller's command port.
    // the 0xFE value is a command byte that tells the keyboard controller to generate a system reset pulse
    outb(0x64, 0xFE);
    asm volatile("cli; hlt");
}

void halt(void)
{
    outw(0x604, 0x2000);
    asm volatile("cli; hlt");
}


void init_shell()
{
    char buffer[256];
    uintptr_t ebp;
	uintptr_t esp;
    while (1)
    {
        k_putstr("42> ", VGA_COLOR_CYAN);
        k_memset(buffer, 0, 256);
        get_line(buffer, 256);
        if (k_strlen(buffer) > 0)
        {
            if (k_strcmp(buffer, "clear") == 0)
            {
                clear_screen();
            }
            if (k_strcmp(buffer, "stack") == 0)
            {
                GET_EBP(ebp);
				GET_ESP(esp);
				k_print("EBP: 0x%08x  ESP: 0x%08x\n", ebp, esp);
				print_memory(esp, ebp - esp);
            }
            if (k_strcmp(buffer, "reboot") == 0)
            {
                reboot();
            }
            if (k_strcmp(buffer, "halt") == 0)
            {
                halt();
            }
        }
    }
}