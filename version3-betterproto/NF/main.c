#include <CONNAC.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pcap.h>
#define LENGTH	10
#define ETHERNET_TYPE_IP              0x0800
#define ETHERNET_TYPE_ARP             0x0806
#define IP_PROTO_TCP                  6
#define IP_PROTO_UDP                  17


int conn_id;
int action_id;


typedef struct _connline{
    struct _connline * prior;
    uint16_t hw_proto;            /* layer2 protocol */
    uint8_t  proto;               /* IP protocoll type */
    int data;
    int cxid;
    int hash;
    struct _connline * next;
}connline;

typedef struct _line{
    struct _line * prior;
    int data;
    int cxid;
    int hash;
    struct _line * next;
}line;

typedef struct
{
    int cxid;
    int hash;

}Match;


connline *conn_head[LENGTH];
connline *conn_put_head[LENGTH];
line *action_head[LENGTH];
line *action_put_head[LENGTH];
void cxt_init();

void conn_initLine_Hash();
void conn_initLine(connline* conn_head_line, int hash);
void show_conn_line();
void show_final_conn_line();

void action_initLine_Hash();
void action_initLine(line* action_head_line, int hash);
void show_action_line();
void show_final_action_line();




int local_conn_get_perflow(Key key);
int local_conn_put_perflow(ConnState* state);

int local_action_get_perflow();
int local_action_get_one_perflow(int hash, int cxid);
int local_action_put_perflow(ActionState* state);


pthread_mutex_t ConnEntryLock;
pthread_mutex_t ActionEntryLock;

pthread_mutex_t ActionOneEntryLock;
pthread_mutex_t ActionCreateEntryLock;

int conn_msg_count;
int action_msg_count;

static void *action_sender(void *arg);
void conn_put_initLine_Hash();
void test_key();

static pthread_t action_thread;

int main()
{
	
    // Conn Table Lock
    pthread_mutex_init(&ConnEntryLock, NULL);

    // Action Table Lock
    pthread_mutex_init(&ActionEntryLock, NULL);

// Action Table Lock
    pthread_mutex_init(&ActionOneEntryLock, NULL);

   pthread_mutex_init(&ActionCreateEntryLock, NULL);

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
    //test_key();
    action_initLine_Hash();   
    //conn_put_initLine_Hash();
	
   
    connac_init(&locals);

    
   
   printf("----------------------");
   while(1){

	}
    
    return 1;
}

void cxt_init()
{
    conn_id = 0;
    action_id = 0;
}

void conn_put_initLine_Hash(){
	
	int i;
	printf("conn_put initline\n");
	for(i = 0; i< 5; i++){
		connline * conn_head_line;
	        conn_head_line =(connline*)malloc(sizeof(connline));
		conn_initLine(conn_head_line,i+1);
		conn_put_head[i]=conn_head_line;
		

	}
	connline * conn_head_line;
	conn_head_line =(connline*)malloc(sizeof(connline));
	conn_initLine(conn_head_line,9);
	conn_put_head[9] = conn_head_line;
	//show_final_conn_line();
	
}

void conn_initLine_Hash(){
	
	int i;
	for(i = 0; i< 5; i++){
		connline * conn_head_line;
	        conn_head_line =(connline*)malloc(sizeof(connline));
		conn_initLine(conn_head_line,i+1);
		conn_head[i]=conn_head_line;
		

	}
	//connline * conn_head_line;
	//conn_head_line =(connline*)malloc(sizeof(connline));
	//conn_initLine(conn_head_line,10);
	//conn_head[9] = conn_head_line;
	//show_conn_line();
	
}

void conn_initLine(connline* conn_head_line, int hash){
    connline* head = conn_head_line;
    
    head->prior=NULL;
    head->next=NULL;

    head->hw_proto = ETHERNET_TYPE_IP; 
    head->proto =IP_PROTO_TCP;
    head->data=1;
    head->hash = hash;
    conn_id++;
    head->cxid = conn_id;
    
    connline * list=head;
    int i;
    for (i=2; i<=5; i++) {
       
        connline * body=(connline*)malloc(sizeof(connline));
        body->prior=NULL;
        body->next=NULL;
        if(2 == i){
		body->hw_proto = ETHERNET_TYPE_ARP ;
	}
	else{
		body->hw_proto = ETHERNET_TYPE_IP; 
	}
	if(3 == i){
		body->proto =IP_PROTO_UDP;
	}
	else{
		body->proto =IP_PROTO_TCP;
	} 
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
        //printf("show conn line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		//printf("show conn line i = %d\n", i);
		while(conn_head[i] != NULL){
			printf("hash = %d ",conn_head[i]->hash);
			printf("data %d ",conn_head[i]->data);
			printf("conn_id = %d ",conn_head[i]->cxid);
			printf("hw_proto= %x ",conn_head[i]-> hw_proto);
			printf("proto = %u\n ",conn_head[i]->proto);
        
        		conn_head[i] = conn_head[i]->next;
		}
	}
}

void show_final_conn_line(){
        printf("show final conn line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		//printf("show conn line i = %d\n", i);
		if(conn_put_head[i] == NULL){
			printf("show conn line NULL %d\n", i);
		}
		while(conn_put_head[i] != NULL){
			printf("hash = %d ",conn_put_head[i]->hash);
			printf("data %d ",conn_put_head[i]->data);
			printf("conn_id = %d ",conn_put_head[i]->cxid);
			printf("hw_proto= %x ",conn_put_head[i]-> hw_proto);
			printf("proto = %u\n",conn_put_head[i]->proto);
        
        
        		conn_put_head[i] =conn_put_head[i]->next;
		}
	}
}





int local_conn_put_perflow(ConnState* state){
    
    printf("receive state, begin to putPerFlow");
    connline * in_state = NULL;
    in_state = (connline*)malloc(sizeof(connline)); 
    int hash = state->hash; 

    in_state->data = state->data; 
    in_state->hash = hash; 
    in_state->cxid = state->cxid; 
    in_state->hw_proto = state->hw_proto; 
    in_state->proto = state->proto; 


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
    
    if(conn_msg_count == 18){
	
	show_final_conn_line();
	}
  
}

void test_key(){
	Key key;
	key.dl_type = 0x800;
	key.nw_proto = 0x6;
	int i;
	for(i = 0; i< LENGTH; i++){
		
		pthread_mutex_lock(&ConnEntryLock);

		while(conn_head[i] != NULL){
			
			if (!(key.wildcards & WILDCARD_DL_TYPE) &&
	                    (conn_head[i]->hw_proto) != key.dl_type)
		            {
		                conn_head[i] = conn_head[i]->next;
		                continue;
		            }
		
		            // Check nw_proto
		        if ((!(key.wildcards & WILDCARD_NW_PROTO)) &&(
	                    (conn_head[i]->proto) != key.nw_proto))
		            {
		                conn_head[i] = conn_head[i]->next;
		                continue;
		            }
			
			printf("conn_head[i]->hash %d",conn_head[i]->hash);
			printf("conn_head[i]->cxid %d\n",conn_head[i]->cxid);
        		conn_head[i] = conn_head[i]->next;
		}
		
		pthread_mutex_unlock(&ConnEntryLock);
			
	}


}


int local_conn_get_perflow(Key key){
        printf("local get per flow\n");

	printf("local  key.dl_type %x\n", key.dl_type);
	printf("key.nw_proto %u\n",key.nw_proto);

	int i;	
	struct timeval start_serialize,end_serialize;
	int count = 0;
	for(i = 0; i< LENGTH; i++){
		
		pthread_mutex_lock(&ConnEntryLock);

		while(conn_head[i] != NULL){
			gettimeofday(&start_serialize, NULL);
			//printf("local key.wildcards & WILDCARD_DL_TYPE %d", key.wildcards & WILDCARD_DL_TYPE);
			//printf("local key.wildcards & WILDCARD_NW_PROTO %d", key.wildcards & WILDCARD_NW_PROTO);
			printf("local ntohs(conn_head[i]->hw_proto) %u\n", conn_head[i]->hw_proto);
			printf("local  key.dl_type %u\n", key.dl_type);

			printf("conn_head[i]->proto) %u\n", conn_head[i]->proto);
			printf("key.nw_proto %u\n",key.nw_proto);

			if (!(key.wildcards & WILDCARD_DL_TYPE) &&
	                    (conn_head[i]->hw_proto) != key.dl_type)
		            {
		                conn_head[i] = conn_head[i]->next;
		                continue;
		            }
		
		            // Check nw_proto
		        if ((!(key.wildcards & WILDCARD_NW_PROTO)) &&(
	                    (conn_head[i]->proto) != key.nw_proto))
		            {
		                conn_head[i] = conn_head[i]->next;
		                continue;
		            }
			
			ConnState connstate;
			conn_state__init(&connstate);

			connstate.has_hw_proto=1;
			connstate.hw_proto = conn_head[i]->hw_proto;
			connstate.has_proto=1;
			connstate.proto = conn_head[i]->proto;
        		connstate.has_data=1;
			connstate.data = conn_head[i]->data;
			int hash = conn_head[i]->hash;			
			connstate.has_hash=1;
			connstate.hash = hash;
			int cxid = conn_head[i]->cxid;
			connstate.has_cxid=1;
			connstate.cxid = cxid;
			
			MyConnMessage mes;
        		my_conn_message__init(&mes);
   
        		mes.data_type = MY_CONN_MESSAGE__DATA_TYPE__ConnStateType;
        		mes.message_case = MY_CONN_MESSAGE__MESSAGE_CONN_STATE;
        		mes.connstate = &connstate;
 
        		int len = my_conn_message__get_packed_size(&mes);
        		printf("size of Perflow : %u\n", len);
        		void *buf = malloc(len);
        		my_conn_message__pack(&mes, buf);

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

			//pthread_mutex_lock(&ActionCreateEntryLock);
			Match* match = (Match*)malloc(sizeof(Match));
			match->hash = hash;
			match->cxid = cxid;
 			printf("local_get_conn hash %d\n", match->hash);
	 		printf("loca_get_conn cxid %d\n", match->cxid);
	
			int err;
			//create a thread to send action state
			if((err = pthread_create(&action_thread, NULL, action_sender, (void*)match))!=0)
               		{
                        perror("pthread_create error");
                	}
			//pthread_mutex_unlock(&ActionCreateEntryLock);
	
        		conn_head[i] = conn_head[i]->next;
		}
		
		pthread_mutex_unlock(&ConnEntryLock);
			
	}
	return count;


}



static void *action_sender(void *arg){

	//pthread_mutex_lock(&ActionOneEntryLock);
	Match *match = (Match*)arg;
	int hash = match->hash;
 	int cxid = match->cxid;
	
	printf("local_get_action hash %d\n", hash);
	printf("local_get_action cxid %d\n", cxid);
	int send_action = local_action_get_one_perflow(hash-1,cxid);
	if(send_action < 0){
		printf("send failed");
	}
	free(match);
	//pthread_mutex_unlock(&ActionOneEntryLock);


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
	action_initLine(action_head_line,10);
	action_head[9] =action_head_line;
	//show_action_line();
	
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
			printf("hash = %d ",action_head[i]->hash);
			printf("data %d ",action_head[i]->data);
			printf("action_id = %d\n",action_head[i]->cxid);
        
        		action_head[i] = action_head[i]->next;
		}
	}
}

void show_final_action_line(){
        printf("show final action line\n");
	int i;	
	for(i = 0; i< LENGTH; i++){
		//printf("show action line i = %d\n", i);
		while(action_put_head[i] != NULL){
			printf("hash = %d ",action_put_head[i]->hash);
			printf("data = %d ",action_put_head[i]->data);
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
    int num = hash-1;
    if(action_put_head[num] != NULL){
         action_put_head[num]->prior = in_state;
	 in_state->next = action_put_head[num]; 
	}
    else{
	
	in_state->next = NULL;
	}
    action_put_head[num] = in_state;
    
    action_msg_count++;
    
    if(action_msg_count == 18){
	
	show_final_action_line();
	}
   
}

int local_action_get_one_perflow(int hash, int cxid){
        printf("local get one action per flow\n");
	struct timeval start_serialize,end_serialize;
	
	pthread_mutex_lock(&ActionEntryLock);
         printf("action begin----------------------\n");
	line* head = action_head[hash];
	while(head != NULL){
		printf("get one action hash before %d\n",hash);
		printf("get one action cxid before %d\n",cxid);
		if(head->cxid != cxid){
			printf("get one action cxid middle %d\n",head->cxid);
			head = head->next;
			continue;
		}
		printf("get one action hash %d\n",hash);
		printf("get one action cxid %d\n",cxid);
		gettimeofday(&start_serialize, NULL);
			
		ActionState actionstate;
		action_state__init(&actionstate);


        	actionstate.has_data=1;
		actionstate.data = head->data;
		actionstate.has_hash=1;
		actionstate.hash = head->hash;
		actionstate.has_cxid=1;
		actionstate.cxid = head->cxid;
		MyActionMessage mes;
        	my_action_message__init(&mes);
   
        	mes.data_type = MY_ACTION_MESSAGE__DATA_TYPE__ActionStateType;
        	mes.message_case = MY_ACTION_MESSAGE__MESSAGE_ACTION_STATE;
        	mes.actionstate = &actionstate;
 
        	int len = my_action_message__get_packed_size(&mes);
        	printf("size of Perflow : %u\n", len);
        	void *buf = malloc(len);
        	my_action_message__pack(&mes, buf);

		int result = action_send_perflow(buf, len);    
       		 if(result < 0){
			return -1;
		}
		
		gettimeofday(&end_serialize, NULL);
		long sec = end_serialize.tv_sec - start_serialize.tv_sec;
        	long usec = end_serialize.tv_usec - start_serialize.tv_usec;
        	long total = (sec * 1000 * 1000) + usec;
        	printf("ACTION STATS: PERFLOW: TIME TO SERIALIZE CURRENT = %ldus\n", total);
		break;
		
			
	}
	printf("action end----------------------\n");
	pthread_mutex_unlock(&ActionEntryLock);
	return 1;
}
	
int local_action_get_perflow(Key key){
        printf("local get action per flow\n");
	int i;	
	struct timeval start_serialize,end_serialize;
	int count = 0;
	for(i = 0; i< LENGTH; i++){
		
		pthread_mutex_lock(&ActionEntryLock);

		while(action_head[i] != NULL){
			gettimeofday(&start_serialize, NULL);

			
			if (action_head[i]->cxid == (i*5+2) || action_head[i]->cxid == (5*5+2))
		            {
				printf("action_head[i] cxid %d", action_head[i]->cxid);		                
				action_head[i] = action_head[i]->next;
		                continue;
		            }
			
		            // Check nw_proto
		        if (action_head[i]->cxid == (i*5+3) || action_head[i]->cxid == (5*5+3))
		            {
				printf("action_head[i] cxid %d", action_head[i]->cxid);			                
				action_head[i] = action_head[i]->next;
		                continue;
		            }
			
			ActionState actionstate;
			action_state__init(&actionstate);


        		actionstate.has_data=1;
			actionstate.data = action_head[i]->data;
			actionstate.has_hash=1;
			actionstate.hash = action_head[i]->hash;
			actionstate.has_cxid=1;
			actionstate.cxid = action_head[i]->cxid;
			MyActionMessage mes;
        		my_action_message__init(&mes);
   
        		mes.data_type = MY_ACTION_MESSAGE__DATA_TYPE__ActionStateType;
        		mes.message_case = MY_ACTION_MESSAGE__MESSAGE_ACTION_STATE;
        		mes.actionstate = &actionstate;
 
        		int len = my_action_message__get_packed_size(&mes);
        		printf("size of Perflow : %u\n", len);
        		void *buf = malloc(len);
        		my_action_message__pack(&mes, buf);

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








