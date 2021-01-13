#include <CONNAC.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>



typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

line* initLine(line * head);

void display(line * head);

void local_get_perflow(){

	printf("begin to get STATES");
}


int main()
{
	
    CONNACLocals locals;
    bzero(&locals,sizeof(locals));
    locals.get_perflow = &local_get_perflow;
    
    connac_init(&locals);

    line * head=NULL;
    
    head=initLine(head);
    
    display(head);
   
    printf("链表中第 4 个节点的直接前驱是：%d\n",head->next->next->next->prior->data);
    
    while(1){

	}
    
    return 1;
}


line* initLine(line * head){
    
    head=(line*)malloc(sizeof(line));
   
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
    
    return head;
}
void display(line * head){
    line * temp=head;
    while (temp) {
        
        if (temp->next==NULL) {
            printf("%d\n",temp->data);
        }else{
            printf("%d <-> ",temp->data);
        }
        temp=temp->next;
    }
}



