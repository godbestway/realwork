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
int local_action_put_perflow(ActionState* state);
int local_conn_put_perflow(ConnState* state);
ProtoObject* proto_compose_conn_perflow_message(int data);
ProtoObject* proto_compose_action_perflow_message(int data);

pthread_mutex_t ConnEntryLock;
pthread_mutex_t ActionEntryLock;


int conn_msg_count;
int action_msg_count;


int main()
{
	
    // Conn Table Lock
    pthread_mutex_init(&ConnEntryLock, NULL);

    // Action Table Lock
    pthread_mutex_init(&ActionEntryLock, NULL);

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
    for (i=2; i<=100; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;
        
        list->next=body;
        body->prior=list;
        
        list=list->next;
    }
    
}


int local_conn_put_perflow(ConnState* state){
    
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
    
    if(conn_msg_count == 100){
	if(conn_put_head->next->next->next->next->next->data != NULL){ 
        	printf("put_head->next->next->next->next->next->data %d\n",conn_put_head->next->next->next->next->next->data);
	}else{
		printf("else put_head->next->next->next->next->data %d\n",conn_put_head->next->next->next->next->data);
	}
	display1();
	}
   
}

int local_action_put_perflow(ActionState* state){
    
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



ProtoObject* proto_compose_conn_perflow_message(int data){
	ConnState conn_perflow =   CONN_STATE__INIT ;
    	conn_perflow.data=data;
    	
    	//check info length  
    	unsigned int len;
    	len = conn_state__get_packed_size(&conn_perflow);
    	printf("send size of perflow : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	conn_state__pack(&conn_perflow, buf);
	
	ProtoObject *conn_perflow_object;
    	conn_perflow_object = (ProtoObject *)malloc(sizeof(ProtoObject));	
	
	//printf("message %d\n",message_type);
	conn_perflow_object->length = len;
	conn_perflow_object->buf = buf;
	conn_perflow_object->message_type=PROTO_CONNPERFLOW;
	
	
	return conn_perflow_object;
	

}

ProtoObject* proto_compose_action_perflow_message(int data){
	ActionState action_perflow = ACTION_STATE__INIT;
    	action_perflow.data=data;
    	
    	//check info length  
    	unsigned int len;
    	len = action_state__get_packed_size(&action_perflow);
    	printf("send size of perflow : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	action_state__pack(&action_perflow, buf);
	
	ProtoObject *action_perflow_object;
    	action_perflow_object = (ProtoObject *)malloc(sizeof(ProtoObject));	
	
	//printf("message %d\n",message_type);
	action_perflow_object->length = len;
	action_perflow_object->buf = buf;
	action_perflow_object->message_type=PROTO_ACTIONPERFLOW;
	
	
	return action_perflow_object;
	

}

int local_action_get_perflow(){
   struct timeval start_serialize, end_lock, end_compose_message,end_send_message, end_serialize;
    int count = 0;
    line * temp= action_head;
    while (temp) {
	gettimeofday(&start_serialize, NULL);
	pthread_mutex_lock(&ActionEntryLock);
        gettimeofday(&end_lock, NULL);
	long sec = end_lock.tv_sec - start_serialize.tv_sec;
        long usec = end_lock.tv_usec - start_serialize.tv_usec;
        long total = (sec * 1000 * 1000) + usec;
        printf("ACTION STATS: PERFLOW: TIME TO add lock CURRENT = %ldus\n", total);

    	ProtoObject *action_perflow_object= NULL;

    	action_perflow_object = proto_compose_action_perflow_message(temp->data);
	gettimeofday(&end_compose_message, NULL);
	sec = end_compose_message.tv_sec - end_lock.tv_sec;
        usec = end_compose_message.tv_usec - end_lock.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("ACTION STATS: PERFLOW: TIME TO compose message CURRENT = %ldus\n", total);
        	
   	int send_success = action_send_perflow(action_perflow_object);
	gettimeofday(&end_send_message, NULL);
	sec = end_send_message.tv_sec - end_compose_message.tv_sec;
        usec = end_send_message.tv_usec - end_compose_message.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("ACTION STATS: PERFLOW: TIME TO send message CURRENT = %ldus\n", total);

    	if(send_success < 0){
		printf("send perflow message failed");
	    	return -1;
        }

        free(action_perflow_object);
    
        temp=temp->next;
	 count++;
        pthread_mutex_unlock(&ActionEntryLock);
	gettimeofday(&end_serialize, NULL);
	sec = end_serialize.tv_sec - start_serialize.tv_sec;
        usec = end_serialize.tv_usec - start_serialize.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("ACTION STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);
    }
    
    
	return count;
}


int local_conn_get_perflow(){
       struct timeval start_serialize, end_lock, end_compose_message,end_send_message,end_serialize;
    int count = 0;
    line * temp= conn_head;
    while (temp) {
	gettimeofday(&start_serialize, NULL);
	pthread_mutex_lock(&ConnEntryLock);
        gettimeofday(&end_lock, NULL);
	long sec = end_lock.tv_sec - start_serialize.tv_sec;
        long usec = end_lock.tv_usec - start_serialize.tv_usec;
        long total = (sec * 1000 * 1000) + usec;
        printf("COON STATS: PERFLOW: TIME TO add lock CURRENT = %ldus\n", total);

    	ProtoObject *conn_perflow_object= NULL;

    	conn_perflow_object = proto_compose_conn_perflow_message(temp->data);
	gettimeofday(&end_compose_message, NULL);
	sec = end_compose_message.tv_sec - end_lock.tv_sec;
        usec = end_compose_message.tv_usec - end_lock.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("CONN STATS: PERFLOW: TIME TO compose message CURRENT = %ldus\n", total);

	
   	int send_success = conn_send_perflow(conn_perflow_object);
	gettimeofday(&end_send_message, NULL);
	sec = end_send_message.tv_sec - end_compose_message.tv_sec;
        usec = end_send_message.tv_usec - end_compose_message.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("CONN STATS: PERFLOW: TIME TO send message CURRENT = %ldus\n", total);

    	if(send_success < 0){
		printf("send perflow message failed");
	    	return -1;
        }

        free(conn_perflow_object);
    
        temp=temp->next;
	 count++;
         pthread_mutex_unlock(&ConnEntryLock);
	gettimeofday(&end_serialize, NULL);
	sec = end_serialize.tv_sec - start_serialize.tv_sec;
        usec = end_serialize.tv_usec - start_serialize.tv_usec;
        total = (sec * 1000 * 1000) + usec;
        printf("CONN STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);
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










