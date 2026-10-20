#include "../../kernel/kernel.h"
#define metadata 6
struct file{
uint32_t* formatbase;
uint32_t* formatlimit;
uint32_t size;
uint32_t* filebase;
uint32_t* filelimit;




}; struct file file[metadata];

//file[2].size=(uint32_t)(file[3].filebase-file[4].filelimit);
//file[3].filebase=(file[3].filebase=file[4].formatlimit+1); //configure the file to the KAT ramdisk file system.

void format_write(void){


//for(uint32_t *i = file[0].formatbase; i!=file[1].formatlimit; *i++)
//{*i = file[i];}


}
