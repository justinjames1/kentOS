#include "kernel.h"
void delay(unsigned long iterations) {
    for (volatile unsigned long i = 0; i < iterations; i++) {
    }
}
