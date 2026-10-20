#include "../../kernel/kernel.h"
int32_t ramio(uint32_t*addr,uint8_t data,uint8_t attr){
uintptr_t*ram_ptr=(uintptr_t*)addr;
if(attr==1){*addr=data;return 1;}
if(attr==0){*addr=data;return *addr;}
return -1;}
