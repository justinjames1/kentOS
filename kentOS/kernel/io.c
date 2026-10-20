#include "kernel.h"
uint8_t Isolated_IO(uint16_t port, uint8_t value, uint8_t attr){
if(attr==0){
__asm__ volatile (
"inb %1,%0"
:"=a"(value)
:"nd"(port));
return value;}
if(attr==1){
__asm__ volatile (
"outb %%al,%%dx"
:
:"a"(value),"d"(port) );
return value;}}

volatile uint32_t* mmio(uint32_t addr,uint32_t value,uint8_t attr){
volatile int32_t*mmio_ptr = (volatile uint32_t *)(uintptr_t)addr;
if(attr==1){*mmio_ptr = value; return mmio_ptr;}
if(attr==0){return mmio_ptr;}
return 0;}


