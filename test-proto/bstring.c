#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstring.pb-c.h"

#define NAME_LEN 32

int main() {
    Bstring bstring = BSTRING__INIT; 
    void *buf = NULL;
    unsigned int len;
    Bstring *msg = NULL;

    bstring.mlen = 5;
    bstring.slen = 10;
    
    bstring.data = (char*)malloc(NAME_LEN);
    bstring.data = "test sffslfs";

    len = bstring__get_packed_size(&bstring);  
    printf("size of Student info : %u\n", len);
    buf = malloc(len);
    bstring__pack(&bstring, buf); 

    msg = bstring__unpack(NULL, len, buf); 
    printf("msg name : %s\n", msg->data);

     bstring__free_unpacked(msg, NULL); 

    free(buf);
    return 0;
}
