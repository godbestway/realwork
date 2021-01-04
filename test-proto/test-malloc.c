#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 #include <stdint.h>
int main(int argc, char *argv[])
{
    uint8_t buf[12];
    uint8_t * buf_2 = NULL;
    uint8_t * buf_3 = NULL;
    int len = 12;
    buf_2 = (uint8_t*)malloc(sizeof(uint8_t)* len);
    buf_3 = (uint8_t*)calloc(len, sizeof(uint8_t));
    

    uint8_t head[4];
    head[0] = 12 & 0xff;
    head[1] = (12 >> 8)&0xff; 
    head[2] = 0;
    head[3] = 0;
	
    int i;
    for(i = 0; i < 4;i++){
	printf("head %d, %u",i,head[i]);
	} 

}
