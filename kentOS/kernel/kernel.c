#define VIDEO_MEMORY_ADDRESS 0xB8000
#include "kernel.h"
char print[256];
char result[256];
int key_char = 0;
void clear(){
short *b = (short*)VIDEO_MEMORY_ADDRESS;
for(int c = 0; c!=80*25; c++){
*b = 0x0000| ' ';
*b++;}}











void kernel_main() {




clear();
IDT();
MCE_init();
pic();
int e = start();


//char argv[] = "Booted. Welcome to KentOS!";

short *t = (short*)VIDEO_MEMORY_ADDRESS;





short *d = (short*)VIDEO_MEMORY_ADDRESS;
for(int a = 0; a!=80*25; a++){
*d++ = 0xAA20;}


void keyboard(){
short *n = (short*)VIDEO_MEMORY_ADDRESS;
for (int k = 0; result[k] != '\0'; k++) {
    n[k] = 0xA000 | (unsigned char)result[k];
}}











while(1){
//__asm__("hlt");


char key = PS2();

if(result!="0"){
result[key_char++] = key;
result[key_char] = '\0';
if(e==1){keyboard();}}

qemuin();

} //kern loop end
  } //kernel_main end 


