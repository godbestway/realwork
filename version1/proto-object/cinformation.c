#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.pb-c.h"
#include "cinformation.pb-c.h"

#define NAME_LEN 32

int main() {
    Cinformation cinfo = CINFORMATION__INIT; 
    uint8_t *buf = NULL;
    unsigned int len;
    Cinformation *msg = NULL;
    
    cinfo.personnum = 10;
    cinfo.content = (char*)malloc(NAME_LEN);
    cinfo.content = "cinfo";
    
    Student stu = STUDENT__INIT;
    stu.name=(char*)malloc(NAME_LEN);
    stu.name="stu";
    cinfo.student = &stu;
 
    cinfo.cinfo = NULL;

    len = cinformation__get_packed_size(&cinfo);  
    printf("size of Student info : %u\n", len);
    buf = (uint8_t*)malloc(len);
    cinformation__pack(&cinfo, buf); 

    msg = cinformation__unpack(NULL, len, buf); 
    printf("msg content : %s\n", msg->content);
    printf("msg stu : %s\n", msg->student->name);
    
    
    Cinformation cinfo1 = CINFORMATION__INIT; 
    Cinformation *cinfo2 = NULL; 
//    *cinfo2 =*msg;    
    cinfo2=msg;
    cinfo1.personnum = 10;
    cinfo1.content = (char*)malloc(NAME_LEN);
    cinfo1.content = "cinfo1";

    cinfo2->cinfo = &cinfo1;
    printf("msg info1 %s\n",cinfo2->cinfo->content);


//    cinformation__free_unpacked(msg, NULL); 
    free(buf);
    return 0;
}
