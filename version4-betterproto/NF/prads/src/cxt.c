#include <assert.h>
#include <sys/time.h>
#include <string.h>
#include "common.h"
#include "prads.h"
#include "cxt.h"
#include "sys_func.h"
#include "config.h"
#include "output-plugins/log.h"
#include "assets.h"
#include "local.h"
#include <CONNAC.h>

extern globalconfig config;

uint64_t cxtrackerid;
static pthread_t conn_thread;
static pthread_t action_thread;
connection *bucket[BUCKET_SIZE];

connState *conn_bucket[BUCKET_SIZE];
actionState *action_bucket[BUCKET_SIZE];

static void put_asset(asset* ori_asset, Asset *in_asset);
static void *conn_sender(void *arg);
static void *action_sender(void *arg);

void cxt_init()
{
    cxtrackerid = 0;
}



int local_conn_put_perflow(ConnState* recv_state){
	
    printf("receive conn state, begin to putPerFlow\n");
    pthread_mutex_lock(&ConnEntryLock);
    //connState *conn_state = NULL;
    connState *conn_state =(connState*)malloc(sizeof(connState));
    int i;
    int m;
    for(i =0; i< 6;i++){
        //printf("recv_state->ether_dst[i] %u",recv_state->ether_dst[i]);
	conn_state->ether_dst[i]=recv_state->ether_dst[i];
	//printf("conn_state->ether_dst[i] %u",conn_state->ether_dst[i]);

    }
    for(m =0; m< 6;m++){
	//printf("recv_state->ether_src[m] %u",recv_state->ether_src[m]);
	conn_state->ether_src[m]=recv_state->ether_src[m];
	//printf("conn_state->ether_src[m] %u",conn_state->ether_src[m]);

    }
	
    struct in6_addr ips;
    struct in6_addr ipd;
    ips.s6_addr32[0] = recv_state->s_ip;
    ipd.s6_addr32[0] = recv_state->d_ip;
    conn_state->s_ip = ips;
    conn_state->d_ip = ipd;

    conn_state->s_port = recv_state->s_port;
    conn_state->d_port = recv_state->d_port;

    uint64_t cxid = recv_state->cxid;
    conn_state->cxid = cxid;
   

    //set a right number of cxtrackerid
    if(cxid > cxtrackerid){
	cxtrackerid = cxid;
    }
   
    uint32_t hash = recv_state->hash;
    conn_state->hash = hash;

    conn_state->hw_proto = recv_state->hw_proto;
    conn_state->proto = recv_state->proto;
    connState* head = conn_bucket[hash];

    // Add to linked list
    conn_state->prev = NULL;
    if (head != NULL)
    {
        head->prev = conn_state;
        conn_state->next = head;
    }
    else
    { 
	conn_state->next = NULL; 
    }
    conn_bucket[hash] = conn_state;
    //showPutConnState();
//+++
    connac_notify_flow_created();
//+++


    printf("\n--------------check first time--------------------\n");
    //showAllCxid();
    pthread_mutex_unlock(&ConnEntryLock);
  
  return 1;

}


int local_action_put_perflow(ActionState* recv_state){
	
    printf("receive action state, begin to putPerFlow");
    pthread_mutex_lock(&ActionEntryLock);
    actionState *action_state = NULL;
    action_state =(actionState*)malloc(sizeof(actionState));

    action_state->start_time = recv_state->start_time;
    action_state->last_pkt_time = recv_state->last_pkt_time;
    action_state->cxid = recv_state->cxid;
    action_state->reversed = recv_state->reversed;
    action_state->af = recv_state->af;
    action_state->s_total_pkts = recv_state->s_total_pkts;
    action_state->s_total_bytes= recv_state->s_total_bytes;
    action_state->d_total_pkts = recv_state->d_total_pkts;
    action_state->d_total_bytes = recv_state->d_total_bytes;
    action_state->s_tcpFlags = recv_state->s_tcpflags;
    action_state->__pad__ = recv_state->pad;
    action_state->d_tcpFlags = recv_state->d_tcpflags;  
    action_state->check = recv_state->check;
	
    uint32_t hash = recv_state->hash;
    action_state->hash = hash;

    actionState* head = action_bucket[hash];

    // Add to linked list
    action_state->prev = NULL;
    if (head != NULL)
    {
        head->prev = action_state;
        action_state->next = head;
    }
    else
    { action_state->next = NULL; }
    action_bucket[hash] = action_state;
    //showPutActionState();
    pthread_mutex_unlock(&ActionEntryLock);
    // If asset structure is present push it into the asset list.
    if(recv_state->c_asset != NULL){
	printf("\n--------------c_asset exits--------------------\n");
	asset* c_asset = (asset*)malloc(sizeof(asset));
	put_asset(c_asset, recv_state->c_asset);

    }
    if(recv_state->s_asset != NULL){
	printf("\n--------------s_asset exits--------------------\n");
	asset* s_asset = (asset*)malloc(sizeof(asset));
	put_asset(s_asset, recv_state->s_asset);
    }

    pthread_mutex_unlock(&ActionEntryLock);
	
    //action_state->c_asset = NULL; 
    //action_state->s_asset = NULL;  
  
    return 1;
}

static void put_asset(asset* ori_asset, Asset *in_asset){

	printf("\n--------------check put asset--------------------\n");
        
	ori_asset->first_seen = in_asset->first_seen;   	
	ori_asset->last_seen = in_asset->last_seen;
	ori_asset->i_attempts = in_asset->i_attempts;
	ori_asset->af = in_asset->af;
	ori_asset->vlan = in_asset->vlan;
	ori_asset->ip_addr.s6_addr32[0] = in_asset->s_ip;
	ori_asset->last_seen = in_asset->last_seen;
	//ori_asset->removed = 1;

	serv_asset* services;
	os_asset* os;
	if(in_asset->services != NULL){
		serv_asset* services = (serv_asset*)malloc(sizeof(serv_asset));
		printf("\n--------------check put services init--------------------\n");

		services->first_seen= in_asset->services->first_seen;
		services->last_seen= in_asset->services->last_seen;
		services->i_attempts= in_asset->services->i_attempts;
		services->proto= in_asset->services->proto;
		services->port= in_asset->services->port;
		services->ttl= in_asset->services->ttl;

		bstring service= (bstring)malloc(sizeof(tagBstring));
		service->mlen= in_asset->services->bservice->mlen;
		service->slen= in_asset->services->bservice->slen;
		service->data= in_asset->services->bservice->data;
		services->service =service;


		bstring application= (bstring)malloc(sizeof(tagBstring));
		application->mlen= in_asset->services->bapplication->mlen;
		application->slen= in_asset->services->bapplication->slen;
		application->data= in_asset->services->bapplication->data;
		services->application =application;

		services->role= in_asset->services->role;
		services->unknown= in_asset->services->unknown;
  		printf("\n--------------check put services finished--------------------\n");
		ori_asset->services = services;

	}
	
	if(in_asset->os != NULL){
		os_asset* os = (os_asset*)malloc(sizeof(os_asset));
		printf("\n--------------check put os init --------------------\n");
		os->first_seen= in_asset->os->first_seen;
		os->last_seen= in_asset->os->last_seen;
		os->i_attempts= in_asset->os->i_attempts;

		bstring os_string= (bstring)malloc(sizeof(tagBstring));
		os_string->mlen= in_asset->os->bos->mlen;
		os_string->slen= in_asset->os->bos->slen;
		os_string->data= in_asset->os->bos->data;
		os->os = os_string;
	
		bstring vendor= (bstring)malloc(sizeof(tagBstring));
		vendor->mlen= in_asset->os->bvendor->mlen;
		vendor->slen= in_asset->os->bvendor->slen;
		vendor->data= in_asset->os->bvendor->data;
		os->vendor = vendor;

		os->detection= in_asset->os->detection;

		bstring raw_fp= (bstring)malloc(sizeof(tagBstring));
		raw_fp->mlen= in_asset->os->raw_fp->mlen;
		raw_fp->slen= in_asset->os->raw_fp->slen;
		raw_fp->data= in_asset->os->raw_fp->data;
		os->raw_fp = raw_fp;

		bstring matched_fp= (bstring)malloc(sizeof(tagBstring));
		matched_fp->mlen= in_asset->os->matched_fp->mlen;
		matched_fp->slen= in_asset->os->matched_fp->slen;
		matched_fp->data= in_asset->os->matched_fp->data;
		os->matched_fp = matched_fp;
		

		os->match_os= in_asset->os->match_os;
		os->match_desc= in_asset->os->match_desc;
  
		os->port= in_asset->os->port;
		os->ttl= in_asset->os->ttl;
		os->mtu= in_asset->os->mtu;
		os->uptime= in_asset->os->uptime;

		printf("\n--------------check put os finished --------------------\n");
		ori_asset->os = os;
	}

	printf("\n--------------check put asset before put asset per sip--------------------\n");
	put_asset_per_sip(in_asset->s_ip, ori_asset);
}




void showPutConnState(){
 int h;
 //store the cxid number of conn state 
 uint64_t conn[100];
 memset(conn, 0, sizeof(conn));
 int count_conn=0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        connState *conn_state = conn_bucket[h];


        while (conn_state != NULL)
        { 
            printf("-----------conn----h%d------------\n",h);    
            showConnState(conn_state); 
            conn[count_conn] = conn_state->cxid; 
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }         
	    
    }
    printf("\n");
    printf("count_conn%d\n",count_conn);
    printf("------------------------------------\n");
    int m;
    for(m = 0; m<= count_conn; m++){
	printf("%lu,",conn[m]);
    }
    

}

void showPutActionState(){
 int h;
 //store the cxid number of action state
 uint64_t action[100];
 memset(action, 0, sizeof(action));
 int count_action =0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        actionState *action_state = action_bucket[h];

        
	while (action_state != NULL)
        {     
            printf("-----------action---h%d------------\n",h);
	    showActionState(action_state); 
	    //add the cxid number in the array
            action[count_action] = action_state->cxid; 
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }       
	    
    }
    printf("\n");
    printf("count_action%d\n",count_action);
    printf("------------------------------------\n");
    int n=0;
    for(n = 0; n<= count_action; n++){
	printf("%lu,",action[n]);
    }


}


int local_conn_get_one_perflow(connState* conn_state){
	 printf("local get one conn per flow\n");	
		
	ConnState* conn_perflow = (ConnState*)malloc(sizeof(ConnState));
	conn_state__init(conn_perflow);


        conn_perflow->n_ether_dst = 6;
        conn_perflow->ether_dst = malloc(sizeof(uint32_t)*6);

        int m;
	int n;

	for(m = 0; m < 6; m++){
		conn_perflow->ether_dst[m]=conn_state->ether_dst[m];
	}
   

 	conn_perflow->n_ether_src = 6;
        conn_perflow->ether_src = malloc(sizeof(uint32_t)*6);

	for(n = 0; n < 6; n++){
		conn_perflow->ether_src[n]=conn_state->ether_src[n];
	}

	conn_perflow->has_s_ip = 1;
	conn_perflow->s_ip = conn_state->s_ip.s6_addr32[0];
	conn_perflow->has_d_ip = 1;
	conn_perflow->d_ip = conn_state->d_ip.s6_addr32[0];
	conn_perflow->has_s_port = 1;
        conn_perflow->s_port = conn_state->s_port;
	conn_perflow->has_d_port = 1;
	conn_perflow->d_port = conn_state->d_port;
	conn_perflow->has_hw_proto=1;
	conn_perflow->hw_proto = conn_state->hw_proto;
	conn_perflow->has_proto=1;
	conn_perflow->proto = conn_state->proto;
	int hash = conn_state->hash;			
	conn_perflow->has_hash=1;
	conn_perflow->hash = hash;
	int cxid = conn_state->cxid;
	conn_perflow->has_cxid=1;
	conn_perflow->cxid = cxid;

        MyConnMessage mes;
        my_conn_message__init(&mes);
   
        mes.data_type = MY_CONN_MESSAGE__DATA_TYPE__ConnStateType;
        mes.message_case = MY_CONN_MESSAGE__MESSAGE_CONN_STATE;
        mes.connstate =conn_perflow;
 
        int len = my_conn_message__get_packed_size(&mes);
        //printf("size of Perflow : %u\n", len);
        void *buf = malloc(len);
        my_conn_message__pack(&mes, buf);

	int result = conn_send_perflow(buf, len);    
       	if(result < 0){
			return -1;
	}
	free(buf);
	free(conn_perflow);
			
}



int local_action_get_one_perflow(Match *match){
        printf("local get one action per flow\n");	
        pthread_mutex_lock(&ActionEntryLock);
	int hash = match->hash;
 	int cxid = match->cxid;
	actionState *action_state = action_bucket[hash];
	while(action_state != NULL){
		printf("local get one action per flow ---while find the right action\n");
		if(action_state->cxid != cxid){
			//printf("get one action cxid middle %d\n",head->cxid);
			action_state = action_state->next;
			continue;
		}

		printf("local get one action per flow ---find the action\n");
		//showActionState(action_state);

		ProtoObject *proto_object = serialize_action_state(action_state);
		uint8_t* buf = proto_object->buf;
		int len = proto_object->length;

		int result = action_send_perflow(buf, len);    
       		 if(result < 0){
			return -1;
		}
		action_state = action_state->next;
	        printf("local get one action per flow ---send successful\n");
		free(proto_object);
		break;
		
	}
	//printf("action end----------------------\n");
	pthread_mutex_unlock(&ActionEntryLock);
	printf("local get one action per flow ---unlock\n");
	free(match);
	return 1;
}





static void *conn_sender(void *arg){
	printf("start a conn sender\n");
	
	connState* conn_state = (connState*)arg;
	int send_conn = local_conn_get_one_perflow(conn_state);
	if(send_conn < 0){
		printf("send failed");
	}

	
}

static void *action_sender(void *arg){
	printf("start a action sender\n");
	Match *match = (Match*)arg;
	
	//printf("match hash %d\n", hash);
	//printf("match cxid %d\n", cxid);
	int send_action = local_action_get_one_perflow(match);
	if(send_action < 0){
		printf("send failed");
	}

}

int local_conn_get_perflow(Key key){
     printf("start conn get perflow\n");
     printf("local  key.dl_type %x\n", key.dl_type);
     printf("key.nw_proto %u\n",key.nw_proto);
 
    int count = 0;
    int h = 0;
    for (h = 0; h < BUCKET_SIZE; h++)
    {        
        pthread_mutex_lock(&ConnEntryLock);
        connState *conn_state = conn_bucket[h];
        while (conn_state != NULL)
        {

		
		//printf("local key.wildcards & WILDCARD_DL_TYPE %d\n", key.wildcards & WILDCARD_DL_TYPE);
		//printf("local key.wildcards & WILDCARD_NW_PROTO %d\n", key.wildcards & WILDCARD_NW_PROTO);
		//printf("localconn_head[i]->hw_proto %u\n", conn_state->hw_proto);
		//printf("localconn_head[i]->hw_proto %u\n",ntohs(key.dl_type));
		//printf("ntohs(key.dl_type) %x\n", conn_state->proto);
		if (!(key.wildcards & WILDCARD_DL_TYPE) && conn_state->hw_proto != ntohs(key.dl_type))
			{
		        	conn_state = conn_state->next;
		                continue;
		        }
		
		            // Check nw_proto
		if ((!(key.wildcards & WILDCARD_NW_PROTO)) &&((conn_state->proto) != key.nw_proto))
			{
		                conn_state = conn_state->next;
		                continue;
		        }

	    
	  
	    //if(1 == count){		

		
	     int err;
	     if((err = pthread_create(&conn_thread, NULL, conn_sender, (void*)conn_state))!=0)
             {
             	perror("pthread_create error");
             }
	   

	     
	     Match* match = (Match*)malloc(sizeof(Match));
	     match->hash = conn_state->hash;
	     match->cxid = conn_state->cxid;
 	     //printf("local_get_conn hash %d\n", match->hash);
	     //printf("loca_get_conn cxid %d\n", match->cxid);
	
		
	     //create a thread to send action state
	     if((err = pthread_create(&action_thread, NULL, action_sender, (void*)match))!=0)
             {
                 perror("pthread_create error");
             }
		
	 	//return 1;
	   //}
		count++;	
	
	        
           // Move on to next connection
           conn_state = conn_state->next;
        }
        pthread_mutex_unlock(&ConnEntryLock);
    }
    return count;

}




//+++
void showConnState(connState* conn_state){
    //struct sockaddr_in sa;
    char src_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(conn_state->s_ip), src_str, INET_ADDRSTRLEN);
   
    //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(conn_state->d_ip), dst_str, INET_ADDRSTRLEN);
    


    printf("---------------ConnState------------------\n");

    printf("src_ip %s\n", src_str);
    printf("ds_ip %s\n", dst_str);
    printf("mac_dst %u",conn_state->ether_dst[0]);
    printf(" %u",conn_state->ether_dst[1]);
    printf(" %u",conn_state->ether_dst[2]);
    printf(" %u",conn_state->ether_dst[3]);
    printf(" %u",conn_state->ether_dst[4]);
    printf(" %u\n",conn_state->ether_dst[5]);
    printf("mac_src %u",conn_state->ether_src[0]);
    printf(" %u",conn_state->ether_src[1]);
    printf(" %u",conn_state->ether_src[2]);
    printf(" %u",conn_state->ether_src[3]);
    printf(" %u",conn_state->ether_src[4]);
    printf(" %u\n",conn_state->ether_src[5]);
    printf("s_port %u\n",conn_state->s_port);
    printf("d_port %u\n",conn_state->d_port);
    printf("cxid  %lu\n",conn_state->cxid);
    printf("hash  %u\n",conn_state->hash);
    printf("hw_proto %u\n",conn_state->hw_proto);
    printf("proto %u\n",conn_state->proto);
    printf("---------------ConnState------------------\n");

}

//+++

//+++
void showActionState(actionState* action_state){


    printf("---------------actionState------------------\n");
    printf("start_time %lu\n",action_state->start_time );
    printf("last_pkt_time %lu\n", action_state->last_pkt_time);
    printf("cxid: %lu\n",action_state->cxid);
    printf("reversed: %u\n",action_state->reversed);
    printf("af %u\n",action_state->af);
    //printf("hw_proto %u\n",action_state->hw_proto);
    //printf("proto %u\n",action_state->proto);
    printf("s_total_pkts  %lu\n",action_state->s_total_pkts);
    printf("s_total_bytes %lu\n",action_state->s_total_bytes);
    printf("d_total_pkts %lu\n",action_state->d_total_pkts);
    printf("d_total_bytes %lu\n",action_state->d_total_bytes);
    printf("s_tcpFlags %u\n",action_state->s_tcpFlags);
    printf("d_tcpFlags  %u\n",action_state->d_tcpFlags);
    printf("check %u\n",action_state->check);
    printf("hash  %u\n",action_state->hash);
    printf("---------------actionState------------------\n");

}



void showAllState(){
 int h;
 uint64_t action[100];
 memset(action, 0, sizeof(action));
 uint64_t conn[100];
 memset(conn, 0, sizeof(conn));
 int count_action =0;
 int count_conn=0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        actionState *action_state = action_bucket[h];
        connState *conn_state = conn_bucket[h];


        while (conn_state != NULL)
        { 
            printf("-----------conn----h%d------------\n",h);    
            showConnState(conn_state); 
            conn[count_conn] = conn_state->cxid; 
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }   
	while (action_state != NULL)
        {     
            printf("-----------action---h%d------------\n",h);
	    showActionState(action_state); 
            action[count_action] = action_state->cxid; 
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }             
    }
    printf("\n");
    int i,m,n;
    printf("count_conn%d\n",count_conn);
    printf("------------------------------------\n");
    for(m = 0; m<= count_conn; m++){
	printf("%lu,",conn[m]);
    }
    printf("\n");
    printf("count_action%d\n",count_action);
    printf("------------------------------------\n");
    
    for(n = 0; n<= count_action; n++){
	printf("%lu,",action[n]);
    }


}

void showAllCxid(){
 int h;
 uint64_t action[100];
 uint64_t conn[100];
 int count_action =0;
 int count_conn=0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        actionState *action_state = action_bucket[h];
        connState *conn_state = conn_bucket[h];


        while (conn_state != NULL)
        { 
               
       
            conn[count_conn] = conn_state->cxid; 
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }   
	while (action_state != NULL)
        {     
            
            action[count_action] = action_state->cxid; 
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }          
    }
    
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    int i,m,n;
   
    printf("count_conn%d\n",count_conn);
    
    for(m = 0; m<= count_conn; m++){
	printf("%lu,",conn[m]);
    }
    printf("\n");
    printf("count_action%d\n",count_action);
    
    for(i = 0; n<= count_action; n++){
	printf("%lu,",action[n]);
    }
    printf("\n");
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    

}



connState *conn_cxt_new(packetinfo *pi){
   
    struct in6_addr ips;
    struct in6_addr ipd;
    connState *conn_state;
    cxtrackerid++;
    conn_state = (connState *) calloc(1, sizeof(connState));
    assert(conn_state);
    conn_state->cxid = cxtrackerid;
//+++
    connac_notify_flow_created();
//+++
   
    if(pi-> af== AF_INET6){
        conn_state->s_ip = PI_IP6SRC(pi);
        conn_state->d_ip = PI_IP6DST(pi);
    }else {
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        conn_state->s_ip = ips;
        conn_state->d_ip = ipd;
    }

    conn_state->s_port = pi->s_port;
    conn_state->d_port = pi->d_port;
    conn_state->proto = pi->proto;
    conn_state->hw_proto = ntohs(pi->eth_type);
    

    conn_state->hash = pi->hash;
    pi->cxid = cxtrackerid;
    

    
    //uint8_t *ether_dst = (uint8_t*)malloc(6);
    conn_state->ether_dst[0] = pi->eth_hdr->ether_dst[0];        /* destination MAC */
    conn_state->ether_dst[1] = pi->eth_hdr->ether_dst[1];        /* destination MAC */
    conn_state->ether_dst[2] = pi->eth_hdr->ether_dst[2];        /* destination MAC */
    conn_state->ether_dst[3] = pi->eth_hdr->ether_dst[3];        /* destination MAC */
    conn_state->ether_dst[4] = pi->eth_hdr->ether_dst[4];        /* destination MAC */
    conn_state->ether_dst[5] = pi->eth_hdr->ether_dst[5];        /* destination MAC */ 
    
    //uint8_t *ether_src = (uint8_t*)malloc(6);
    
    conn_state->ether_src[0] = pi->eth_hdr->ether_src[0];        /* src MAC */
    conn_state->ether_src[1] = pi->eth_hdr->ether_src[1];        /* src MAC */
    conn_state->ether_src[2] = pi->eth_hdr->ether_src[2];        /* src MAC */
    conn_state->ether_src[3] = pi->eth_hdr->ether_src[3];        /* src MAC */
    conn_state->ether_src[4] = pi->eth_hdr->ether_src[4];        /* src MAC */
    conn_state->ether_src[5] = pi->eth_hdr->ether_src[5];        /* src MAC */


    //showConnState(conn_state);

    return conn_state;
 

}
//+++

//+++

/* freshly smelling connection :d */
actionState *action_cxt_new(packetinfo *pi)
{


    //printf("create a new action");
    actionState *action_state;
    
    action_state = (actionState *) calloc(1, sizeof(actionState));
    assert(action_state);
    action_state->cxid = cxtrackerid;
    action_state->hash = pi->hash;
//+++
    //connac_notify_flow_created();
//+++
    action_state->af = pi->af;
    if(pi->tcph) action_state->s_tcpFlags = pi->tcph->t_flags;
    //cxt->s_tcpFlags |= (pi->tcph ? pi->tcph->t_flags : 0x00);//why??
    //cxt->d_tcpFlags = 0x00;
    action_state->s_total_bytes = pi->packet_bytes;
    action_state->s_total_pkts = 1;
    action_state->start_time = pi->pheader->ts.tv_sec;
    action_state->last_pkt_time = pi->pheader->ts.tv_sec; 
    action_state->check = 0x00;
    action_state->c_asset = NULL;
    action_state->s_asset = NULL;
    action_state->reversed = 0;


    //action_state->proto = pi->proto;
    //action_state->hw_proto = ntohs(pi->eth_type); 
    //showActionState(action_state);
     
    
    return action_state;
}

//+++

/* freshly smelling connection :d */
connection *cxt_new(packetinfo *pi)
{

    struct in6_addr ips;
    struct in6_addr ipd;
    connection *cxt;
    cxtrackerid++;
    cxt = (connection *) calloc(1, sizeof(connection));
    assert(cxt);
    cxt->cxid = cxtrackerid;
//+++
    connac_notify_flow_created();
//+++
    cxt->af = pi->af;
    if(pi->tcph) cxt->s_tcpFlags = pi->tcph->t_flags;
    //cxt->s_tcpFlags |= (pi->tcph ? pi->tcph->t_flags : 0x00);//why??
    //cxt->d_tcpFlags = 0x00;
    cxt->s_total_bytes = pi->packet_bytes;
    cxt->s_total_pkts = 1;
    cxt->start_time = pi->pheader->ts.tv_sec;
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi-> af== AF_INET6){
        cxt->s_ip = PI_IP6SRC(pi);
        cxt->d_ip = PI_IP6DST(pi);
    }else {
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        cxt->s_ip = ips;
        cxt->d_ip = ipd;
    }

    cxt->s_port = pi->s_port;
    cxt->d_port = pi->d_port;
    cxt->proto = pi->proto;
    cxt->hw_proto = ntohs(pi->eth_type);

    cxt->check = 0x00;
    cxt->c_asset = NULL;
    cxt->s_asset = NULL;
    cxt->reversed = 0;

    //showConnection(cxt);
    showAllCxid();

    return cxt;
}

//+++
int action_tracking(packetinfo *pi)
{
    //static char ip_addr_s[INET6_ADDRSTRLEN];
    //static char ip_addr_d[INET6_ADDRSTRLEN];
    action_cx_track(pi);

    return 0;
}
//+++

//+++
int conn_tracking(packetinfo *pi)
{
    //static char ip_addr_s[INET6_ADDRSTRLEN];
    //static char ip_addr_d[INET6_ADDRSTRLEN];
    conn_cx_track(pi);

    return 0;
}
//+++


int connection_tracking(packetinfo *pi)
{
    static char ip_addr_s[INET6_ADDRSTRLEN];
    static char ip_addr_d[INET6_ADDRSTRLEN];
    cx_track(pi);
    
    if(config.cflags & CONFIG_CONNECT){
	//log_connection(pi->cxt, CX_EXCESSIVE);
    }
    return 0;
}

//+++
int action_update_client(actionState *action_state, packetinfo *pi)
{
    action_state->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) action_state->s_tcpFlags |= pi->tcph->t_flags;
    action_state->s_total_bytes += pi->packet_bytes;
    action_state->s_total_pkts += 1;

    pi->action_state = action_state;
    if(!action_state->c_asset)
        action_state->c_asset = pi->asset; // connection client asset
    if (action_state->s_total_bytes > MAX_BYTE_CHECK
        || action_state->s_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont Check!
    }
    //printf("action------SC_CLIENT ----------------------------\n");
    //showActionState(action_state);
    return SC_CLIENT;
}
//+++

int cxt_update_client(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->s_tcpFlags |= pi->tcph->t_flags;
    cxt->s_total_bytes += pi->packet_bytes;
    cxt->s_total_pkts += 1;

    //pi->cxt = cxt;
    pi->sc = SC_CLIENT;
    if(!cxt->c_asset)
        cxt->c_asset = pi->asset; // connection client asset
    if (cxt->s_total_bytes > MAX_BYTE_CHECK
        || cxt->s_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont Check!
    }
    //printf("connection -----SC_CLIENT ----------------------------\n");
    //showConnection(cxt);
    return SC_CLIENT;
}

//+++
int action_update_server(actionState *action_state, packetinfo *pi)
{
    action_state->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) action_state->d_tcpFlags |= pi->tcph->t_flags;
    action_state->d_total_bytes += pi->packet_bytes;
    action_state->d_total_pkts += 1;

    pi->action_state = action_state;
    if(!action_state->s_asset)
        action_state->s_asset = pi->asset; // server asset
    if (action_state->d_total_bytes > MAX_BYTE_CHECK
        || action_state->d_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont check!
    }
    //printf("action------SC_SERVER ----------------------------\n");
    //showActionState(action_state);
    return SC_SERVER;

}
//+++


int cxt_update_server(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->d_tcpFlags |= pi->tcph->t_flags;
    cxt->d_total_bytes += pi->packet_bytes;
    cxt->d_total_pkts += 1;

    //pi->cxt = cxt;
    pi->sc = SC_SERVER;
    if(!cxt->s_asset)
        cxt->s_asset = pi->asset; // server asset
    if (cxt->d_total_bytes > MAX_BYTE_CHECK
        || cxt->d_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont check!
    }
    //printf("connection-------SC_SERVER ----------------------------\n");
    //showConnection(cxt);
    return SC_SERVER;

}




//+++
int conn_cx_track(packetinfo *pi){

  
    struct in6_addr *ip_src;
    struct in6_addr *ip_dst;
    struct in6_addr ips;
    struct in6_addr ipd;
    uint16_t src_port = pi->s_port;
    uint16_t dst_port = pi->d_port;
       
    connState *conn_state = NULL;
    connState *head = NULL;
    uint32_t hash;

    int af = pi->af;
    if(af== AF_INET6){
        ip_src = &PI_IP6SRC(pi);
        ip_dst = &PI_IP6DST(pi);
    }else {
        // ugly hack :(
        // the way we do ip4/6 is DIRTY
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        ip_src = &ips;
        ip_dst = &ipd;
    }

    // find the right connection bucket
    if (af == AF_INET) {
        hash = CXT_HASH4(IP4ADDR(ip_src),IP4ADDR(ip_dst),src_port,dst_port,pi->proto);
    } else if (af == AF_INET6) {
        hash = CXT_HASH6(ip_src,ip_dst,src_port,dst_port,pi->proto);
    }
    pi->hash= hash;
    conn_state = conn_bucket[hash];
    head = conn_state;

    // search through the bucket
    // 
    uint64_t cxid = 0;
    while (conn_state != NULL) {
        // Two-way compare of given connection against connection table
        if (af == AF_INET) {
            if (CMP_CXT4(conn_state,IP4ADDR(ip_src),src_port,IP4ADDR(ip_dst),dst_port)){
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
		cxid = conn_state ->cxid;
                pi->sc = SC_CLIENT;
               //printf("this is client find the conn state\n");
            } else if (CMP_CXT4(conn_state,IP4ADDR(ip_dst),dst_port,IP4ADDR(ip_src),src_port)) {
                // This is a server (Maybe not when we start up but in the long run)
                cxid = conn_state ->cxid;
		pi->sc = SC_SERVER;
		//printf("this is server find the conn state\n");
            }
        } else if (af == AF_INET6) {
            if (CMP_CXT6(conn_state,ip_src,src_port,ip_dst,dst_port)){
                cxid = conn_state ->cxid;
		pi->sc = SC_CLIENT;
            } else if (CMP_CXT6(conn_state,ip_dst,dst_port,ip_src,src_port)){
                cxid = conn_state ->cxid;
		pi->sc = SC_SERVER;
            }
        }
        conn_state = conn_state->next;
    }
    pi->cxid = cxid; 
   // bucket turned upside down didn't yeild anything. new connection
    if(cxid == 0)
    {
	conn_state = conn_cxt_new(pi);
        //log_connection(conn_state, CX_NEW);

    	/* * New connections are pushed on to the head of bucket[s_hash] */
    	conn_state->next = head;
   	 if (head != NULL) 
	{
        	// are we doubly linked?
        	head->prev = conn_state;
    	}
    	conn_bucket[hash] = conn_state;
    	pi->conn_state = conn_state;
    }
    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}
//+++



/* return value: client or server?
 *** USED TO BE: 0 = dont check, 1 = client, 2 = server
 * now returns 0, SC_CLIENT(=1), SC_SERVER(=2)
 */

int cx_track(packetinfo *pi) {

   
    struct in6_addr *ip_src;
    struct in6_addr *ip_dst;
    struct in6_addr ips;
    struct in6_addr ipd;
    uint16_t src_port = pi->s_port;
    uint16_t dst_port = pi->d_port;
    int af = pi->af;
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;


    if(af== AF_INET6){
        ip_src = &PI_IP6SRC(pi);
        ip_dst = &PI_IP6DST(pi);
    }else {
        // ugly hack :(
        // the way we do ip4/6 is DIRTY
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        ip_src = &ips;
        ip_dst = &ipd;
    }

    // find the right connection bucket
    if (af == AF_INET) {
        hash = CXT_HASH4(IP4ADDR(ip_src),IP4ADDR(ip_dst),src_port,dst_port,pi->proto);
    } else if (af == AF_INET6) {
        hash = CXT_HASH6(ip_src,ip_dst,src_port,dst_port,pi->proto);
    }
    cxt = bucket[hash];
    head = cxt;

    // search through the bucket
    while (cxt != NULL) {
        // Two-way compare of given connection against connection table
        if (af == AF_INET) {
            if (CMP_CXT4(cxt,IP4ADDR(ip_src),src_port,IP4ADDR(ip_dst),dst_port)){
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
		//printf("connection---find the number SC-CLIENT\n");
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT4(cxt,IP4ADDR(ip_dst),dst_port,IP4ADDR(ip_src),src_port)) {
                // This is a server (Maybe not when we start up but in the long run)
		//printf("connection---find the number SC-SERVER\n");
                return cxt_update_server(cxt, pi);
            }
        } else if (af == AF_INET6) {
            if (CMP_CXT6(cxt,ip_src,src_port,ip_dst,dst_port)){
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT6(cxt,ip_dst,dst_port,ip_src,src_port)){
                return cxt_update_server(cxt, pi);
            }
        }
        cxt = cxt->next;
    }
    // bucket turned upside down didn't yeild anything. new connection
    cxt = cxt_new(pi);
    log_connection(cxt, CX_NEW);

    /* * New connections are pushed on to the head of bucket[s_hash] */
    cxt->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = cxt;
    }
    bucket[hash] = cxt;
    //pi->cxt = cxt;
    printf("----------------------endcx_track---------------------------\n");
    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}


int action_cx_track(packetinfo *pi) {
    
    int af = pi->af;
    actionState *action_state = NULL;
    actionState *head = NULL;
    
    uint32_t hash;
    uint64_t cxid;

    hash = pi->hash;
    
    action_state = action_bucket[hash];
    head = action_state;

    // search through the bucket
    while (action_state != NULL) {
        // Two-way compare of given connection against connection table
        cxid = action_state->cxid;
        if (af == AF_INET) {
	    /*printf("action-----action_state cxid: %lu\n",cxid);
            printf("action-----packet cxid: %lu\n",pi->cxid);
            if(pi->sc ==  SC_SERVER){
		printf("action----packet is from SC_SERVER\n");
	    }
	    else{
		printf("action----packet is from SC_CLIENT\n");

		}
            */
            if ((pi->sc == SC_CLIENT) &(pi->cxid == cxid)){
                //printf("action---find the number SC-CLIENT, cxid: %lu\n",pi->cxid);
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
                return action_update_client(action_state, pi);
            } else if ((pi->sc == SC_SERVER)&(pi->cxid == cxid)) {
                // This is a server (Maybe not when we start up but in the long run)
		//printf("action---find the number SC-SERVER, cxid: %lu\n",pi->cxid);
                return action_update_server(action_state, pi);
            }
        } else if (af == AF_INET6) {
            if ((pi->sc == SC_CLIENT) &(pi->cxid == cxid)){
                return action_update_client(action_state, pi);
            } else if ((pi->sc = SC_SERVER)&(pi->cxid == cxid)){
                return action_update_server(action_state, pi);
            }
        }
        action_state = action_state->next;
    }
    // bucket turned upside down didn't yeild anything. new connection
    action_state = action_cxt_new(pi);
    //log_connection(cxt, CX_NEW);

    /* * New connections are pushed on to the head of bucket[s_hash] */
    action_state->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = action_state;
    }
    action_bucket[hash] = action_state;
    pi->action_state = action_state;

    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}

void reverse_pi_cxt(packetinfo *pi)
{
    uint8_t tmpFlags;
    uint64_t tmp_pkts;
    uint64_t tmp_bytes;
    struct in6_addr tmp_ip;
    uint16_t tmp_port;
    connection *cxt;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!reverse pi cxt\n");

    //cxt = pi->cxt;

    /* First we chang the cxt */
    /* cp src to tmp */
    tmpFlags = cxt->s_tcpFlags;
    tmp_pkts = cxt->s_total_pkts;
    tmp_bytes = cxt->s_total_bytes;
    tmp_ip = cxt->s_ip;
    tmp_port = cxt->s_port;

    /* cp dst to src */
    cxt->s_tcpFlags = cxt->d_tcpFlags;
    cxt->s_total_pkts = cxt->d_total_pkts;
    cxt->s_total_bytes = cxt->d_total_bytes;
    cxt->s_ip = cxt->d_ip;
    cxt->s_port = cxt->d_port;

    /* cp tmp to dst */
    cxt->d_tcpFlags = tmpFlags; 
    cxt->d_total_pkts = tmp_pkts;
    cxt->d_total_bytes = tmp_bytes;
    cxt->d_ip = tmp_ip;
    cxt->d_port = tmp_port;

    /* Not taking any chances :P */
    cxt->c_asset = cxt->s_asset = NULL;
    cxt->check = 0x00;

    /* Then we change pi */
    if (pi->sc == SC_CLIENT)
       pi->sc = SC_SERVER;
    else
       pi->sc = SC_CLIENT;
}


void reverse_pi_conn_action(packetinfo *pi)
{
    uint8_t tmpFlags;
    uint64_t tmp_pkts;
    uint64_t tmp_bytes;
    struct in6_addr tmp_ip;
    uint16_t tmp_port;
    actionState *action_state;
    connState *conn_state;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!reverse pi cxt\n");

    action_state = pi->action_state;
    conn_state = pi->conn_state;
    

    /* First we chang the cxt */
    /* cp src to tmp */
    tmpFlags = action_state->s_tcpFlags;
    tmp_pkts = action_state->s_total_pkts;
    tmp_bytes = action_state->s_total_bytes;
    tmp_ip = conn_state->s_ip;
    tmp_port = conn_state->s_port;

    /* cp dst to src */
    action_state->s_tcpFlags = action_state->d_tcpFlags;
    action_state->s_total_pkts = action_state->d_total_pkts;
    action_state->s_total_bytes = action_state->d_total_bytes;
    conn_state->s_ip = conn_state->d_ip;
    conn_state->s_port = conn_state->d_port;

    /* cp tmp to dst */
    action_state->d_tcpFlags = tmpFlags; 
    action_state->d_total_pkts = tmp_pkts;
    action_state->d_total_bytes = tmp_bytes;
    conn_state->d_ip = tmp_ip;
    conn_state->d_port = tmp_port;

    /* Not taking any chances :P */
    action_state->c_asset = action_state->s_asset = NULL;
    action_state->check = 0x00;

    /* Then we change pi */
    if (pi->sc == SC_CLIENT)
       pi->sc = SC_SERVER;
    else
       pi->sc = SC_CLIENT;
}


/*
 This sub marks sessions as ENDED on different criterias:

 XXX: May be the fugliest code in PRADS :-(
*/

void end_sessions()
{
   printf("-------------------------------end sessions--------------------------------------\n");

    connection *cxt;
    int iter;
    int cxstatus = CX_NONE;
    int ended, expired = 0;
    uint32_t curcxt = 0;
    time_t check_time = time(NULL);

    log_rotate(check_time);
    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        cxt = bucket[iter];
        while (cxt != NULL) {
            curcxt++;
            /* TCP */
            if (cxt->proto == IP_PROTO_TCP) {
                /* * FIN from both sides */
                if (cxt->s_tcpFlags & TF_FIN && cxt->d_tcpFlags & TF_FIN
                    && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                } /* * RST from either side */
                else if ((cxt->s_tcpFlags & TF_RST
                          || cxt->d_tcpFlags & TF_RST)
                          && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                }
                else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* UDP */
            else if (cxt->proto == IP_PROTO_UDP
                     && (check_time - cxt->last_pkt_time) > 60) {
                cxstatus = CX_EXPIRE;
            }
            /* ICMP */
            else if (cxt->proto == IP_PROTO_ICMP
                     || cxt->proto == IP6_PROTO_ICMP) {
                if ((check_time - cxt->last_pkt_time) > 60) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* All Other protocols */
            else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                cxstatus = CX_EXPIRE;
            }

            if (cxstatus == CX_ENDED || cxstatus == CX_EXPIRE) {
                /* remove from the hash */
                if (cxt->prev)
                    cxt->prev->next = cxt->next;
                if (cxt->next)
                    cxt->next->prev = cxt->prev;
                connection *tmp = cxt;

                log_connection(cxt, cxstatus);
                cxstatus = CX_NONE;

                cxt = cxt->prev;

                del_connection(tmp, &bucket[iter]);
                if (cxt == NULL) {
                    bucket[iter] = NULL;
                }
            } else {
                cxt = cxt->prev;
            }
        } // end while cxt
    } // end for buckets
}


void end_connac_sessions()
{
   printf("-------------------------------end connac sessions--------------------------------------\n");

    connState *conn_state;
    actionState *action_state;
    int iter;
    int cxstatus = CX_NONE;
    int ended, expired = 0;
    uint32_t curcxt = 0;
    time_t check_time = time(NULL);

    log_rotate(check_time);
    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        conn_state = conn_bucket[iter];
        action_state = action_bucket[iter];

        while (action_state != NULL) {
            curcxt++;
            /* TCP */
            if (conn_state->proto == IP_PROTO_TCP) {
                /* * FIN from both sides */
                if (action_state->s_tcpFlags & TF_FIN && action_state->d_tcpFlags & TF_FIN
                    && (check_time - action_state->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                } /* * RST from either side */
                else if ((action_state->s_tcpFlags & TF_RST
                          || action_state->d_tcpFlags & TF_RST)
                          && (check_time - action_state->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                }
                else if ((check_time - action_state->last_pkt_time) > TCP_TIMEOUT) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* UDP */
            else if (conn_state->proto == IP_PROTO_UDP
                     && (check_time - action_state->last_pkt_time) > 60) {
                cxstatus = CX_EXPIRE;
            }
            /* ICMP */
            else if (conn_state->proto == IP_PROTO_ICMP
                     || conn_state->proto == IP6_PROTO_ICMP) {
                if ((check_time - action_state->last_pkt_time) > 60) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* All Other protocols */
            else if ((check_time - action_state->last_pkt_time) > TCP_TIMEOUT) {
                cxstatus = CX_EXPIRE;
            }

            if (cxstatus == CX_ENDED || cxstatus == CX_EXPIRE) {
                 while (conn_state != NULL)
        	{ 
		if(conn_state->cxid == action_state->cxid){
			break;
		}            	    
			conn_state = conn_state->next;	
        	}   
		/* remove from the hash */
                if (conn_state->prev)
                    conn_state->prev->next = conn_state->next;
                if (conn_state->next)
                    conn_state->next->prev = conn_state->prev;
                connState *conn_tmp = conn_state;

                conn_state = conn_state->prev;

                del_conn_state(conn_tmp, &conn_bucket[iter]);
                if (conn_state == NULL) {
                    conn_bucket[iter] = NULL;
                }
                
                /* remove from the hash */
                if (action_state->prev)
                    action_state->prev->next = action_state->next;
                if (action_state->next)
                    action_state->next->prev = action_state->prev;
                actionState *tmp = action_state;

                
                cxstatus = CX_NONE;

                action_state = action_state->prev;

                del_action_state(tmp, &action_bucket[iter]);
                if (action_state == NULL) {
                    action_bucket[iter] = NULL;
                }
            } else {
                action_state = action_state->prev;
            }
        } // end while cxt
    } // end for buckets
}


void log_connection_all()
{
    int i;
    connection *cxt;
    if(! (config.cflags & CONFIG_CXWRITE))
        return;
    for(i = 0; i < BUCKET_SIZE; i++) {
        cxt = bucket[i];
        while(cxt) {
            log_connection(cxt, CX_HUMAN);
            cxt = cxt->next;
        }
    }
}



void del_conn_state(connState * conn_state, connState ** bucket_ptr)
{
    connState *prev = conn_state->prev;       /* OLDER connections */
    connState *next = conn_state->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }
    connac_notify_flow_destroyed();
    /*
     * Free and set to NULL 
     */
    free(conn_state);
    conn_state = NULL;
}

void del_action_state(actionState * action_state, actionState ** bucket_ptr)
{
    actionState *prev = action_state->prev;       /* OLDER connections */
    actionState *next = action_state->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }

    /*
     * Free and set to NULL 
     */
    free(action_state);
    action_state = NULL;
}


void del_connection(connection * cxt, connection ** bucket_ptr)
{
    connection *prev = cxt->prev;       /* OLDER connections */
    connection *next = cxt->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }

    /*
     * Free and set to NULL 
     */
    free(cxt);
    cxt = NULL;
}

void end_all_sessions()
{
    connection *cxt;
    int cxkey;
    FILE *cxtFile = NULL;

    log_rotate(time(NULL));
    for (cxkey = 0; cxkey < BUCKET_SIZE; cxkey++) {
        cxt = bucket[cxkey];
        while (cxt != NULL) {
            connection *tmp = cxt;

            log_connection(cxt, CX_ENDED);
            cxt = cxt->next;
            del_connection(tmp, &bucket[cxkey]);
            if (cxt == NULL) {
                bucket[cxkey] = NULL;
            }
        }
    }
    if (cxtFile != NULL) {
        fclose(cxtFile);
    }
}

void cxt_log_buckets(int dummy)
{
    connection *cxt = NULL;
    FILE *logfile = NULL;
    int i;
    int len;

    logfile = fopen("/tmp/prads-buckets.log", "w");
    if (!logfile)
        return;

    dlog("Recieved SIGUSR1 - Dumping bucketlist to logfile\n");
    for (i = 0; i < BUCKET_SIZE; i++) {
        len = 0;
        for (cxt = bucket[i]; cxt; cxt = cxt->next)
            len++;
        if (len > 0)
            fprintf(logfile, "%d in bucket[%5d]\n", len, i);
    }

    fflush(logfile);
    fclose(logfile);
}



/* vector comparisons to speed up cx tracking.
 * meaning, compare source:port and dest:port at the same time.
 *
 * about vectors and potential improvements:
 * * all 64bit machines have at least SSE2 instructions * *BUT* there is no guarantee we won't loose time on
 * copying the vectors around.
 * ... indeed, a quick objdump shows us that
 * there is a shitton of mov instructions to align the addresses.
 *
 * Needs support to give improvements: 
 * the addresses should already be aligned as a 128-bit word
 * in the connection tracking bucket.
 *
 * note, we can employ the same technique for ipv6 addresses, but
 * one address at a time.
 */
#ifdef VECTOR_CXTRACKER
// vector fill: srcprt,dstprt,srcip,dstip = 96 bytes. rest is 0
#define VEC_FILL(vec, _ipsrc,_ipdst,_portsrc,_portdst) do {\
    vec.s[0] = (_portsrc); \
    vec.s[1] = (_portdst); \
    vec.w[1] = (_ipsrc); \
    vec.w[2] = (_ipdst); \
    vec.w[3] = 0; \
} while (0)

inline void cx_track_simd_ipv4(packetinfo *pi)
{
    printf("use cx_track_simd_ipv4\n");
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;

    // add to packetinfo ? dont through int32 around :)
    hash = make_hash(pi);
    cxt = bucket[hash];
    head = cxt;

    ip6v incoming;
    ip6v compare;
    VEC_FILL(incoming,
        pi->ip_src.__u6_addr.__u6_addr32[0],
        pi->ip_dst.__u6_addr.__u6_addr32[0],
        pi->s_port,
        pi->d_port);
    while (cxt != NULL   
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_port,
        cxt->d_port);

        // single-instruction compare -msse2
        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        // same thing, really. c == v iff c ^ v == 0
        //compare.v = compare.v ^ incoming.v;

        // 64-bit compare reduce
        if(!(compare.i[0] & compare.i[1])){
            //ok
            dlog("[*] Updating src connection: %lu\n",cxt->cxid);
            cxt_update_src(cxt,pi);
            return;
        }

        // compare the other direction
        VEC_FILL(compare,
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_port,
        cxt->s_port); 

        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        if(!(compare.i[0] & compare.i[1])){
            dlog("[*] Updating dst connection: %lu\n",cxt->cxid);
            cxt_update_dst(cxt,pi);
            return;
        }
        cxt = cxt->next;
    }
    if (cxt == NULL) {
        cxt = (connection *) connection_alloc();
        //cxt = (connection *) calloc(1, sizeof(connection));
        if (head != NULL) {
            head->prev = cxt;
        }
        cxt = cxt_new(pi);
        dlog("[*] New connection: %lu\n",cxt->cxid);
        cxt->next = head;
        bucket[hash] = cxt;
        return;
    }
    printf("[*] Error in session tracking...\n");
    exit (1);
}



#endif
