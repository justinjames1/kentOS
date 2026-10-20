#include "kernel.h"

#define VIDEO_MEMORY_ADDRESS 0xB8000
char os_name[7] = { 'K', 'E', 'N', 'T', 'O', 'S', '\0' };

char cpu_name[6] = { 'C', 'P', 'U', ':', ' ', '\0' };

char ram_name[6] = { 'R', 'A', 'M', ':', ' ', '\0' };


int start(uint32_t leaf, char out_vendor[13]) {
    char ven[13];
    cpuid(0,ven); 
    ven[12] = '\0';

    volatile short *t = (volatile short*)VIDEO_MEMORY_ADDRESS;

short *b = (short*)VIDEO_MEMORY_ADDRESS;
for(int a = 0; a!=80*25; a++){
*b++ = 0x1F00;}


    for (int i = 0; os_name[i] != '\0' && i < 12; i++) {
        t[i] = 0x1F00 | (unsigned char)os_name[i];
    }


t = (short*)VIDEO_MEMORY_ADDRESS + 80;

    // Print "cpu:"
    int k = 0;
    while (cpu_name[k] != '\0') {
        t[k] = 0x1F00 | (unsigned char)cpu_name[k]; // White on black
        k++;
    }

    // Print vendor string after cpu_name
    int offset = k;
    for (int i = 0; ven[i] != '\0' && i < 12; i++) {
        t[offset + i] = 0x1F00 | (unsigned char)ven[i];
    }

t = (short*)VIDEO_MEMORY_ADDRESS + 160;

    for (int i = 0; ram_name[i] != '\0' && i < 12; i++) {
        t[i] = 0x1F00 | (unsigned char)ram_name[i];
    }





delay(200000000);


return 1;





}
