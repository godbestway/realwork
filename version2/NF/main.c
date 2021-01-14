#include "flowstate.pb-c.h"
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

line head;

void initLine(line * head);

int local_get_perflow();
ProtoObject* proto_compose_perflow_message(int data);



int main()
{
	
    CONNACLocals locals;
    bzero(&locals,sizeof(locals));
    locals.get_perflow = &local_get_perflow;
	
    initLine(&head);
    
    connac_init(&locals);

    
   
   // printf("链表中第 4 个节点的直接前驱是：%d\n",head->next->next->prior->data);
    
    while(1){

	}
    
    return 1;
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


ProtoObject* proto_compose_perflow_message(int data){
	FlowState perflow = FLOW_STATE__INIT;
    	perflow.data=data;
    	
    	//check info length  
    	unsigned int len;
    	len = flow_state__get_packed_size(&perflow);
    	printf("send size of perflow : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	flow_state__pack(&perflow, buf);
	
	ProtoObject *perflow_object;
    	perflow_object = (ProtoObject *)malloc(sizeof(ProtoObject));	
	
	//printf("message %d\n",message_type);
	perflow_object->length = len;
	perflow_object->buf = buf;
	perflow_object->message_type=PROTO_CONNPERFLOW;
	
	
	return perflow_object;
	

}

int local_get_perflow(){
    line * temp= &head;
    while (temp) {

    	ProtoObject *perflow_object	= NULL;

    	perflow_object = proto_compose_perflow_message(temp->data);	
   	int send_success = connac_send_perflow(perflow_object);

    	if(send_success < 0){
		printf("send perflow message failed");
	    	return -1;
        }

        free(perflow_object);
    
        temp=temp->next;
    }
	return 1;
}











