// misc/MCE.c
#include <stdint.h>


// READ an MSR
static uint64_t rdmsr(uint32_t index)
{
    uint32_t low, high;

    __asm__ volatile (
        "rdmsr"
        : "=a"(low), "=d"(high)
        : "c"(index)
    );

    return ((uint64_t)high << 32) | low;
}

// WRITE an MSR
static void wrmsr(uint32_t index, uint64_t value)
{
    uint32_t low  = (uint32_t)value;
    uint32_t high = (uint32_t)(value >> 32);

    __asm__ volatile (
        "wrmsr"
        :
        : "c"(index), "a"(low), "d"(high)
        : "memory"
    );
}

int MCE_init(void)
{

uint32_t cr4;
__asm__ volatile ("mov %%cr4,%0" : "=r"(cr4));
cr4 |= 0x40;
__asm__ volatile (
    "mov %0, %%cr4"
    :
    : "r"(cr4)
    : "memory"
);

uint64_t cap = rdmsr(0x179);  // IA32_MCG_CAP

if (cap & (1ULL << 8)) {
    wrmsr(0x17B, UINT64_MAX); // IA32_MCG_CTL
}

wrmsr(0x400,(uint64_t)0xFFFFFFFFFFFFFFFF);






    return 1;
}
