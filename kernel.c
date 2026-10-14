#define VIDEO_MEMORY_ADDRESS 0xB8000


void kernel_main() {

volatile short *ptr=(volatile short*)VIDEO_MEMORY_ADDRESS;

char argv[] = "Booted.";

short *t = (short*)VIDEO_MEMORY_ADDRESS;
*t--;




short *b = (short*)VIDEO_MEMORY_ADDRESS;
for(int c = 0; c!=3000; c++){
*b++;
*b = 0x0000 | ' ';}


short *d = (short*)VIDEO_MEMORY_ADDRESS;
for(int a = 0; a!=3000; a++){
*d++;
*d = 0xAAAA | ' ';}




for(int i = 0;argv[i]!='\0';i++){

*t++;
*t = 0xA000 | argv[i];


}


while(1){
__asm__("hlt");}
}

