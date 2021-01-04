#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.pb-c.h"
#include <sys/time.h>

#define NAME_LEN 32

int main() {
    Struct stu = STRUCT__INIT; 
    uint8_t *buf = NULL;
    unsigned int len;
    Struct *msg = NULL;

    stu.a=1;
    stu.b=2;
    stu.c=3;
    stu.d=4;
    stu.e=5;
    stu.f=6;
    stu.g=7;
    stu.h=8;
    stu.i=9;
    stu.j=10;
    stu.k=11;
    stu.l=12;

    len = struct__get_packed_size(&stu);  
    printf("size of Student info : %u\n", len);
    buf = (uint8_t*)malloc(len);
    
    struct__pack(&stu, buf); 
    struct timeval start_serialize, end_serialize;
    gettimeofday(&start_serialize, NULL);

    msg = struct__unpack(NULL, len, buf); 
    gettimeofday(&end_serialize, NULL);
    long sec = end_serialize.tv_sec - start_serialize.tv_sec;
    long usec = end_serialize.tv_usec - start_serialize.tv_usec;
    long total = (sec * 1000 * 1000) + usec;
    printf("STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);


    printf("msg name : %u\n", msg->a);

    struct__free_unpacked(msg, NULL); 

    free(buf);
    return 0;
}
