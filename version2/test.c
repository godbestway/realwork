#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

line head;

void initLine(line * head);

int local_get_perflow();

 
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
    int pid = getpid();
    char hostname[1024];
    memset(hostname, 0, 1024);
    gethostname(hostname, 1024);    
    printf("hostname %s\n", hostname);
    printf("pid %d\n",pid);
    
     initLine(&head);
     local_get_perflow();
    
//    printf("int: %d\n",b);
   
}

void initLine(line * head){
    
   
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    
    line * list=head;
    int i;
    for (i=2; i<=5; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;

        
        list->next=body;
        body->prior=list;
        
        list=list->next;
    }
    
}


int local_get_perflow(){
    line * temp= &head;
    while (temp) { 
       
    printf("while data: %d\n",temp->data);
    temp=temp->next;
    }
	return 1;
}
