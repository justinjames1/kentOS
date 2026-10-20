#ifndef IO_H
#define IO_H
volatile uint32_t* mmio(uint32_t addr, uint32_t value, uint8_t attr);
uint8_t Isolated_IO(uint16_t port, uint8_t value, uint8_t attr);
#endif
