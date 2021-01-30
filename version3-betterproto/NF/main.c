#include <CONNAC.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>
#define LENGTH	10


int conn_id;
int action_id;
pthread_mutex_t ConnEntryLock;
typedef struct line{
    struct line * prior;
    int data;
    int cxid;
    int hash;
    struct line * next;
}line;

line *conn_head[LENGTH];
line *conn_put_head[LENGTH];
line *action_head[LENGTH];
line *action_put_head[LENGTH];
void cxt_init();

void conn_initLine_Hash();
void conn_initLine(line* conn_head_line, int hash);
void show_conn_line();
void show_final_conn_line();

void action_initLine_Hash();
void action_initLine(line* action_head_line, int hash);
void show_action_line();
void show_final_action_line();


void display(line * head);
void display1();
void display2();

int local_conn_get_perflow();
int local_conn_put_perflow(ConnState* state);

int local_action_get_perflow();
int local_action_put_perflow(ActionState* state);


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
    //conn_head=(line*)malloc(sizeof(line));
    //conn_put_head=(line*)malloc(sizeof(line));
    //action_head=(line*)malloc(sizeof(line));
    //action_put_head=(line*)malloc(sizeof(line));
    cxt_init();    

    conn_initLine_Hash();
    //conn_initLine();
    action_initLine_Hash();   
    

    connac_init(&locals);

    
   
  
    while(1){

	}
    
    return 1;
}

void cxt_init()
{
    conn_id = 0;
    action_id = 0;
}



void conn_initLine_Hash(){
	
	int i;
	for(i = 0; i< 5; i++){
		line * conn_head_line;
	        conn_head_line =(line*)malloc(sizeof(line));
		conn_initLine(conn_head_line,i+1);
		conn_head[i]=conn_head_line;
		

	}
	line * conn_head_line;
	conn_head_line =(line*)malloc(sizeof(line));
	conn_initLine(conn_head_line,9);
	conn_head[9] = conn_head_line;
	//show_conn_line();
	
}

void conn_initLine(line* conn_head_line, int hash){

    line* head = conn_head_line;
    
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    head->hash = hash;
    conn_id++;
    head->cxid = conn_id;
    
    line * list=head;
    int i;
    for (i=2; i<=5; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;
	body->hash = hash;
	conn_id++;
        body->cxid = conn_id;
        
        list->next=body;
        body->prior=list;
        
        list=list->next;
    }
    
}

void show_conn_line(){
        printf("show conn line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		printf("show conn line i = %d\n", i);
		while(conn_head[i] != NULL){
			printf("hash = %d\n",conn_head[i]->hash);
			printf("data %d\n",conn_head[i]->data);
			printf("conn_id = %d\n",conn_head[i]->cxid);
        
        		conn_head[i] = conn_head[i]->next;
		}
	}
}

void show_final_conn_line(){
        printf("show conn line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		printf("show conn line i = %d\n", i);
		while(conn_put_head[i] != NULL){
			printf("hash = %d\n",conn_put_head[i]->hash);
			printf("data %d\n",conn_put_head[i]->data);
			printf("conn_id = %d\n",conn_put_head[i]->cxid);
        
        		conn_put_head[i] =conn_put_head[i]->next;
		}
	}
}





int local_conn_put_perflow(ConnState* state){
    
    printf("receive state, begin to putPerFlow");
    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    int hash = state->hash; 

    in_state->data = state->data; 
    in_state->hash = hash; 
    in_state->cxid = state->cxid; 

     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(conn_put_head[hash] != NULL){
         conn_put_head[hash]->prior = in_state;
	 in_state->next = conn_put_head[hash]; 
	}
    else{
	
	in_state->next = NULL;
	}
    conn_put_head[hash] = in_state;
    
    conn_msg_count++;
    
  if(conn_msg_count == 30){
	
	show_final_conn_line();
	}
  
}


int local_conn_get_perflow(){
        printf("local get per flow\n");
	int i;	
	struct timeval start_serialize,end_serialize;
	int count = 0;
	for(i = 0; i< LENGTH; i++){
		
		pthread_mutex_lock(&ConnEntryLock);

		while(conn_head[i] != NULL){
			gettimeofday(&start_serialize, NULL);
			
			ConnState connstate;
			conn_state__init(&connstate);


        		connstate.has_data=1;
			connstate.data = conn_head[i]->data;
			connstate.has_hash=1;
			connstate.hash = conn_head[i]->hash;
			connstate.has_cxid=1;
			connstate.cxid = conn_head[i]->cxid;
			MyMessage mes;
        		my_message__init(&mes);
   
        		mes.data_type = MY_MESSAGE__DATA_TYPE__ConnStateType;
        		mes.message_case = MY_MESSAGE__MESSAGE_CONN_STATE;
        		mes.connstate = &connstate;
 
        		int len = my_message__get_packed_size(&mes);
        		printf("size of Perflow : %u\n", len);
        		void *buf = malloc(len);
        		my_message__pack(&mes, buf);

			int result = conn_send_perflow(buf, len);    
       		 	if(result < 0){
				return -1;
			}
			 count++;
			gettimeofday(&end_serialize, NULL);
			long sec = end_serialize.tv_sec - start_serialize.tv_sec;
        		long usec = end_serialize.tv_usec - start_serialize.tv_usec;
        		long total = (sec * 1000 * 1000) + usec;
        		printf("CONN STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);

			
        
        		conn_head[i] = conn_head[i]->next;
		}
		
		pthread_mutex_unlock(&ConnEntryLock);
			
	}
	return count;


}


void action_initLine_Hash(){
	
	int i;
	for(i = 0; i< 5; i++){
		line * action_head_line;
	        action_head_line =(line*)malloc(sizeof(line));
		action_initLine(action_head_line,i+1);
		action_head[i]=action_head_line;
		

	}
	line * action_head_line;
	action_head_line =(line*)malloc(sizeof(line));
	action_initLine(action_head_line,9);
	action_head[9] =action_head_line;
	//show_conn_line();
	
}




void action_initLine(line* action_head_line, int hash){
    
    line* head = action_head_line;
    
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    head->hash = hash;
    action_id++;
    head->cxid = action_id;
    
    line * list= head;
    int i;
    for (i=2; i<=5; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;
	body->hash = hash;
	action_id++;
        body->cxid = action_id;
        
        list->next=body;
        body->prior=list;
        
        list=list->next;
    }
    
}



void show_action_line(){
        printf("show action line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		printf("show action line i = %d\n", i);
		while(action_head[i] != NULL){
			printf("hash = %d\n",action_head[i]->hash);
			printf("data %d\n",action_head[i]->data);
			printf("action_id = %d\n",action_head[i]->cxid);
        
        		action_head[i] = action_head[i]->next;
		}
	}
}

void show_final_action_line(){
        printf("show action line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		printf("show action line i = %d\n", i);
		while(action_put_head[i] != NULL){
			printf("hash = %d\n",action_put_head[i]->hash);
			printf("data %d\n",action_put_head[i]->data);
			printf("conn_id = %d\n",action_put_head[i]->cxid);
        
        		action_put_head[i] =action_put_head[i]->next;
		}
	}
}



int local_action_put_perflow(ActionState* state){
    
    printf("receive action state, begin to putPerFlow");
    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    int hash = state->hash;

    in_state->data = state->data; 
    in_state->hash = hash; 
    in_state->cxid = state->cxid; 

     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(action_put_head[hash] != NULL){
         action_put_head[hash]->prior = in_state;
	 in_state->next = action_put_head[hash]; 
	}
    else{
	
	in_state->next = NULL;
	}
    action_put_head[hash] = in_state;
    
    action_msg_count++;
    
    if(action_msg_count == 30){
	
	show_final_action_line();
	}
   
}

	
int local_action_get_perflow(){
        printf("local get action per flow\n");
	int i;	
	struct timeval start_serialize,end_serialize;
	int count = 0;
	for(i = 0; i< LENGTH; i++){
		
		pthread_mutex_lock(&ActionEntryLock);

		while(action_head[i] != NULL){
			gettimeofday(&start_serialize, NULL);
			
			ActionState actionstate;
			action_state__init(&actionstate);


        		actionstate.has_data=1;
			actionstate.data = action_head[i]->data;
			actionstate.has_hash=1;
			actionstate.hash = action_head[i]->hash;
			actionstate.has_cxid=1;
			actionstate.cxid = action_head[i]->cxid;
			MyMessage mes;
        		my_message__init(&mes);
   
        		mes.data_type = MY_MESSAGE__DATA_TYPE__ActionStateType;
        		mes.message_case = MY_MESSAGE__MESSAGE_ACTION_STATE;
        		mes.actionstate = &actionstate;
 
        		int len = my_message__get_packed_size(&mes);
        		printf("size of Perflow : %u\n", len);
        		void *buf = malloc(len);
        		my_message__pack(&mes, buf);

			int result = action_send_perflow(buf, len);    
       		 	if(result < 0){
				return -1;
			}
			count++;
			gettimeofday(&end_serialize, NULL);
			long sec = end_serialize.tv_sec - start_serialize.tv_sec;
        		long usec = end_serialize.tv_usec - start_serialize.tv_usec;
        		long total = (sec * 1000 * 1000) + usec;
        		printf("CONN STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);

			
        
        		action_head[i] = action_head[i]->next;
		}
		
		pthread_mutex_unlock(&ActionEntryLock);
			
	}
	return count;


}
	
	


       


/*

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

*/








