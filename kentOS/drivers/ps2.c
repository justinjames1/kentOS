#include "kernel/kernel.h"
int respond = 0;
char key[];
int key_2;


static inline int8_t inb(int16_t port,int8_t value){
__asm__ volatile (
"inb %1,%0"
:"=a"(value)
:"nd"(port));
return value;
}



static inline void outb(int16_t port, int8_t value){


__asm__ volatile (
"outb %%al,%%dx"
:
:"a"(value),"d"(port) );
//return value;
}



int PS2(void) {
    if (!(inb(0x64,NULL) & 1))
        return -1;

    return inb(0x60,NULL);
}



