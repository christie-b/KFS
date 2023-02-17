// const unsigned char keyboard_mapping[128] =
// {
//   0,
//   27, // ascii code for escape key
//   '1','2','3','4','5','6','7','8','9','0','-','=',
//   '\b', // Backspace
//   '\t', // Tab
//   'q','w','e','r','t','y','u','i','o','p','[',']',
//   '\n', // Enter
//   0, // left Ctrl
//   'a','s','d','f','g','h','j','k','l',';','\'','`',
//   0, // left Shift
//   '\\','z','x','c','v','b','n','m',',','.','/',
//   0, // right Shift
//   '*', // numpad asterisk
//   0, // left Alt
//   ' ', // Spacebar
//   0,
// };


#include "kernel.h"  
#include "keyboard.h"  
#include "source.h"
#include "io.h"
// #include <sys/io.h>

int clicked = 0;
int canSend = 0;

unsigned char get_scancode()
{
    unsigned char inputdata;
    inputdata = inb(0x60);
    return inputdata;
}



void keyboard_handler()
{
    unsigned char scancode;
    unsigned int shift_key = 0;


    canSend = 0;

    scancode = get_scancode();
    if (scancode == 0x2A)
    {
        shift_key = 1;//Shift key is pressed
    }
    else if (scancode & 0xAA)
    {
        int shift_key = 0;//Shift Key is not pressed
    }

    if (scancode & 0x80)
    {
        int shiftaltctrl = 1;//Put anything to see what special keys were pressed
    }
    else
    {
        char character;
        if (scancode == 0x0F) {
            clicked = 0; // tab, resets stuff
            clear_screen();
        }

        if (scancode == 0x01) {
            clicked = 0;
        }

        if (scancode == 0x1E && clicked == 0) {
           
            character = 'a';
            clicked = 1;
            canSend = 1;
           
        }
        if (scancode == 0x30 && clicked == 0) {

            character = 'b';
            clicked = 1;
            canSend = 1;

        }
        if (scancode == 0x2E && clicked == 0) {

            character = 'c';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x20 && clicked == 0) {

            character = 'd';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x12 && clicked == 0) {

            character = 'e';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x21 && clicked == 0) {

            character = 'f';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x22 && clicked == 0) {

            character = 'g';
            clicked = 1;
            canSend = 1;
        }

        if (scancode == 0x23 && clicked == 0) {

            character = 'h';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x17 && clicked == 0) {

            character = 'i';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x24 && clicked == 0) {

            character = 'j';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x25 && clicked == 0) {

            character = 'k';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x26 && clicked == 0) {

            character = 'l';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x32 && clicked == 0) {

            character = 'm';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x31 && clicked == 0) {

            character = 'n';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x18 && clicked == 0) {

            character = 'o';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x19 && clicked == 0) {

            character = 'p';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x10 && clicked == 0) {

            character = 'q';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x13 && clicked == 0) {

            character = 'r';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x1F && clicked == 0) {

            character = 's';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x14 && clicked == 0) {

            character = 't';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x16 && clicked == 0) {

            character = 'u';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x2F && clicked == 0) {

            character = 'v';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x11 && clicked == 0) {

            character = 'w';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x2D && clicked == 0) {

            character = 'x';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x15 && clicked == 0) {

            character = 'y';
            clicked = 1;
            canSend = 1;
        }
        if (scancode == 0x2c && clicked == 0) {

            character = 'z';
            clicked = 1;
            canSend = 1;
        }

        
        //print_char(character, RED);
        if (canSend == 1) {
            vga_index += 10;
            print_char(character, VGA_COLOR_CYAN);
        }
    }

}

// https://meepy.medium.com/creating-a-kernel-from-scratch-1a1aa569780f