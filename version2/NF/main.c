#include "flowstate.pb-c.h"
#include <CONNAC.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>


pthread_mutex_t ConnEntryLock;
typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

line* head;
line* put_head;
int msg_count = 0;

void initLine();
void display(line * head);
void display2();

int local_get_perflow();
int local_put_perflow();
ProtoObject* proto_compose_perflow_message(int data);



int main()
{
	
    CONNACLocals locals;
    bzero(&locals,sizeof(locals));
    locals.conn_get_perflow = &local_get_perflow;
    locals.conn_put_perflow = &local_put_perflow;
    head=(line*)malloc(sizeof(line));
    put_head=(line*)malloc(sizeof(line));
    
	
    /*if(put_head -> data == NULL){
		printf("at first put_head = NULL\n");
	}
    else{
		printf("at first put_head = %d\n",put_head -> data);
	}*/
    initLine();
    
    connac_init(&locals);

    
   
   // printf("链表中第 4 个节点的直接前驱是：%d\n",head->next->next->prior->data);
    
    while(1){

	}
    
    return 1;
}


void initLine(){
    
   
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


int local_put_perflow(FlowState* state){

    printf("receive state, begin to putPerFlow");
    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    in_state->data = state->data; 
     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(put_head != NULL){
         put_head->prior = in_state;
	 in_state->next = put_head; 
	}
    else{
	
	in_state->next = NULL;
	}
    put_head = in_state;
    
    msg_count++;
    
    if(msg_count == 5){
	if(put_head->next->next->next->next->next->data != NULL){ 
        	printf("put_head->next->next->next->next->next->data %d\n",put_head->next->next->next->next->next->data);
	}else{
		printf("else put_head->next->next->next->next->data %d\n",put_head->next->next->next->next->data);
	}
	display2();
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
    int count = 0;
    line * temp= head;
    while (temp) {

    	ProtoObject *perflow_object= NULL;

    	perflow_object = proto_compose_perflow_message(temp->data);	
   	int send_success = conn_send_perflow(perflow_object);

    	if(send_success < 0){
		printf("send perflow message failed");
	    	return -1;
        }

        free(perflow_object);
    
        temp=temp->next;
	 count++;
    }
    
    
	return count;
}

void display(line * input){
    line * temp=input;
    while (temp) {
        
        if (temp->next==NULL) {
            printf("%d\n",temp->data);
        }else{
            printf("%d <-> ",temp->data);
        }
        temp=temp->next;
    }
}

void display2(){
    while (put_head->next != NULL) {
        
        
        printf("!!!%d <-> ",put_head->data);
        
        put_head=put_head->next;
    }
}









