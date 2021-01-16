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

line* conn_head;
line* conn_put_head;
line* action_head;
line* action_put_head;

void conn_initLine();
void action_initLine();
void display(line * head);
void display1();
void display2();

int local_conn_get_perflow();
int local_action_get_perflow();
int local_action_put_perflow(FlowState* state);
int local_conn_put_perflow(FlowState* state);
ProtoObject* proto_compose_perflow_message(int data);

int conn_msg_count;
int action_msg_count;


int main()
{
	
    CONNACLocals locals;
    bzero(&locals,sizeof(locals));
    locals.conn_get_perflow = &local_conn_get_perflow;
    locals.conn_put_perflow = &local_conn_put_perflow;
    locals.action_get_perflow = &local_action_get_perflow;
    locals.action_put_perflow = &local_action_put_perflow;
    conn_head=(line*)malloc(sizeof(line));
    conn_put_head=(line*)malloc(sizeof(line));
    action_head=(line*)malloc(sizeof(line));
    action_put_head=(line*)malloc(sizeof(line));
    
	
    /*if(put_head -> data == NULL){
		printf("at first put_head = NULL\n");
	}
    else{
		printf("at first put_head = %d\n",put_head -> data);
	}*/
    conn_initLine();
    action_initLine();   
    connac_init(&locals);

    
   
   // printf("链表中第 4 个节点的直接前驱是：%d\n",head->next->next->prior->data);
    
    while(1){

	}
    
    return 1;
}

void action_initLine(){
    
   
    action_head->prior=NULL;
    action_head->next=NULL;
    action_head->data=1;
    
    line * list=action_head;
    int i;
    for (i=2; i<=8; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;
        
        list->next=body;
        body->prior=list;
        
        list=list->next;
    }
    
}

void conn_initLine(){
    
   
    conn_head->prior=NULL;
    conn_head->next=NULL;
    conn_head->data=1;
    
    line * list=conn_head;
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


int local_conn_put_perflow(FlowState* state){
    
    printf("receive state, begin to putPerFlow");
    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    in_state->data = state->data; 
     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(conn_put_head != NULL){
         conn_put_head->prior = in_state;
	 in_state->next = conn_put_head; 
	}
    else{
	
	in_state->next = NULL;
	}
    conn_put_head = in_state;
    
    conn_msg_count++;
    
    if(conn_msg_count == 5){
	if(conn_put_head->next->next->next->next->next->data != NULL){ 
        	printf("put_head->next->next->next->next->next->data %d\n",conn_put_head->next->next->next->next->next->data);
	}else{
		printf("else put_head->next->next->next->next->data %d\n",conn_put_head->next->next->next->next->data);
	}
	display1();
	}
   
}

int local_action_put_perflow(FlowState* state){
    
    printf("receive state, begin to putPerFlow");
    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    in_state->data = state->data; 
     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(action_put_head != NULL){
         action_put_head->prior = in_state;
	 in_state->next = action_put_head; 
	}
    else{
	
	in_state->next = NULL;
	}
    action_put_head = in_state;
    
    action_msg_count++;
    
    if(action_msg_count == 8){
	if(action_put_head->next->next->next->next->next->data != NULL){ 
        	printf("put_head->next->next->next->next->next->data %d\n",action_put_head->next->next->next->next->next->data);
	}else{
		printf("else put_head->next->next->next->next->data %d\n",action_put_head->next->next->next->next->data);
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

int local_action_get_perflow(){
    int count = 0;
    line * temp= action_head;
    while (temp) {

    	ProtoObject *perflow_object= NULL;

    	perflow_object = proto_compose_perflow_message(temp->data);	
   	int send_success = action_send_perflow(perflow_object);

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


int local_conn_get_perflow(){
    int count = 0;
    line * temp= conn_head;
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
void display1(){
    while (conn_put_head->next != NULL) {
        
        
        printf("!!!%d <-> ",conn_put_head->data);
        
        conn_put_head=conn_put_head->next;
    }
}


void display2(){
    while (action_put_head->next != NULL) {
        
        
        printf("!!!%d <-> ",action_put_head->data);
        
        action_put_head=action_put_head->next;
    }
}









