#include <msgpack.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include "serialize.h"
//#define UNPACKED_BUFFER_SIZE 2048


int main(void) {
    int size;
    //char *state = ser_ialize(head_tra, "some_struct", &first_struct, NULL, 0);
    struct timeval start_serialize, end_serialize;
    gettimeofday(&start_serialize, NULL);    

    //char *buf = prepare(&first_struct,&size);
    //ser_parse(head_tra, "connection", state, NULL);
    gettimeofday(&end_serialize, NULL);
    long sec = end_serialize.tv_sec - start_serialize.tv_sec;
    long usec = end_serialize.tv_usec - start_serialize.tv_usec;
    long total = (sec * 1000 * 1000) + usec;
    printf("STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);

    //some_struct *s = unpack(buf, size);
	

    return 0;
}

/* Output */

/*
Object no 1:
[1, true, "example"]
Object no 2:
"second"
Object no 3:
[42, false]
All msgpack_object in the buffer is consumed.
*/
