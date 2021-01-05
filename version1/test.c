#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
 
int main()
{
    char a[2];
    a[0] = 0x0c;
    a[1] = 12;
    int b; 
    //b = a[1] & 0xff;

    b = (int)((a[0] & 0xff) |( (a[1] & 0xff)<<8));
    char *buf = (char*)malloc(2);

    int c = (int)a[1];
    buf[0] = 0x0a;
    buf[1] = 0x02;
    uint8_t* bufint = (uint8_t*)buf; 
    int j = strlen(buf);
    //printf("strlen %d\n ",c);
    printf("size %x\n", bufint[0]); 
 
//    printf("int: %d\n",b);
   
}

