#include "kernel.h"
#define VIDEO_MEMORY_ADDRESS 0xB8000
int h;
 char error[171] = "system halted due to a fatal error. and needs to be manually restarted.         if restarting doesnt fix try trouble shooting.                                  error code: ";

char exception_DE[5] = "0x00";

void kernel_panic(char errorcode[10]){
while(1){

short *b = (short*)VIDEO_MEMORY_ADDRESS;
for(int a = 0; a!=80*25; a++){
*b++ = 0x1F00;}
short *d = (short*)VIDEO_MEMORY_ADDRESS;

for(int a = 0; a!=80*25; a++){
*d++ = 0x1F00 |error[a];}

d = (short*)VIDEO_MEMORY_ADDRESS + 172;

for (int a =0; errorcode[a]!='\0' && a<10; a++)
{*d++ = 0x1F00 | (unsigned char)errorcode[a];}


while(1){

__asm__
("cli\n"
"hlt\n");  //halt processes 

}}}
