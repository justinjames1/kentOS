#include "kernel.h"
char *cpuid(uint32_t leaf, char vendor[13])
{
    uint32_t eax = leaf, ebx, ecx = 0, edx;

    __asm__ volatile (
        "cpuid"
        : "+a"(eax), "=b"(ebx), "+c"(ecx), "=d"(edx)
    );

    if (leaf == 0) {
        vendor[0]  = (ebx)        & 0xFF;
        vendor[1]  = (ebx >> 8)   & 0xFF;
        vendor[2]  = (ebx >> 16)  & 0xFF;
        vendor[3]  = (ebx >> 24)  & 0xFF;

        vendor[4]  = (edx)        & 0xFF;
        vendor[5]  = (edx >> 8)   & 0xFF; //this is some vuju bullshit.
        vendor[6]  = (edx >> 16)  & 0xFF;
        vendor[7]  = (edx >> 24)  & 0xFF;

        vendor[8]  = (ecx)        & 0xFF;
        vendor[9]  = (ecx >> 8)   & 0xFF;
        vendor[10] = (ecx >> 16)  & 0xFF;
        vendor[11] = (ecx >> 24)  & 0xFF;
        vendor[12] = '\0';
    }

    return vendor;
}

