#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.pb-c.h"

#define NAME_LEN 32

int main() {
    Student stu = STUDENT__INIT; 
    void *buf = NULL;
    unsigned int len;
    Student *msg = NULL;

    stu.name = (char*)malloc(NAME_LEN);
    stu.name = "test";

    len = student__get_packed_size(&stu);  
    printf("size of Student info : %u\n", len);
    buf = malloc(len);
    student__pack(&stu, buf); 

    msg = student__unpack(NULL, len, buf); 
    printf("msg name : %s\n", msg->name);

    student__free_unpacked(msg, NULL); 

    free(buf);
    return 0;
}
