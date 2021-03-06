/*
   Copyright (C) 2010  Infertux <infertux@infertux.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#include "table.h"

extern uint32_t *hash_nat_array[BUCKET_SIZE];
//extern connState *nat_conn_bucket[BUCKET_SIZE];
//extern actionState *nat_action_bucket[BUCKET_SIZE];
connState *conn_bucket[BUCKET_SIZE];
actionState *action_bucket[BUCKET_SIZE];
uint32_t cxtrackerid = 0;

extern pthread_mutex_t ConnEntryLock;
extern pthread_mutex_t ActionEntryLock;
static pthread_t conn_thread;
static pthread_t action_thread;

extern uint32_t ex_ip;


int local_conn_put_perflow(ConnState* recv_state){
	
    printf("receive conn state, begin to putPerFlow\n");
    pthread_mutex_lock(&ConnEntryLock);
    //connState *conn_state = NULL;
    connState *conn_state =(connState*)malloc(sizeof(connState));

    int i;
    for(i =0; i< 6;i++){
	conn_state->internal_mac[i]=recv_state->ether_src[i];
	//printf("conn_state->ether_dst[i] %u",conn_state->ether_dst[i]);

    }
    //memcpy(conn_state->internal_mac, recv_state->ether_src, ETH_ALEN);
    conn_state-> internal_ip = recv_state->s_ip;
    conn_state-> external_ip = recv_state->d_ip;
    conn_state->internal_port = recv_state->s_port;
    conn_state->proto = recv_state->proto;
    
    uint32_t cxid = recv_state->cxid;
    conn_state->cxid = cxid;

    //set a right number of cxtrackerid
    if(cxid > cxtrackerid){
	cxtrackerid = cxid;
    }
   
    uint32_t hash = recv_state->hash;
    conn_state->hash = hash;

    uint32_t nat_hash = recv_state->nat_hash;
    conn_state->nat_hash = nat_hash;

    hash_nat_array[nat_hash] = hash;
//TODO
//    uint32_t nat_hash = CXT_HASH4(ex_ip, IP4ADDR(&ipd), htons(key->tp_src),
//                htons(key->tp_dst), key->nw_proto);


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




//+++
    connac_notify_flow_created();
//+++

//+++advanced part different from normal connac+++
    actionState *action_state = NULL;
    action_state =(actionState*)malloc(sizeof(actionState));

    action_state->external_ip = recv_state->d_ip;
    action_state->touch = time(NULL);
    action_state->cxid = cxid;
    action_state->hash = hash;
    action_state->external_port = table_get_external_port(hash, cxid);

    action_state->nat_hash = nat_hash;
    

    actionState* action_head = action_bucket[hash];

    // Add to linked list
    action_state->prev = NULL;
    if (action_head != NULL)
    {
        action_head->prev = action_state;
        action_state->next = action_head;
    }
    else
    { action_state->next = NULL; }
    action_bucket[hash] = action_state;

//+++advanced part different from normal connac+++
     
    pthread_mutex_unlock(&ConnEntryLock);
  
  return 1;

}



int local_action_put_perflow(ActionState* recv_state){
	
    printf("receive action state, begin to putPerFlow\n");
    pthread_mutex_lock(&ActionEntryLock);
    actionState *action_state = NULL;
    action_state =(actionState*)malloc(sizeof(actionState));

    action_state->external_ip = recv_state->external_ip;
    action_state->external_port = recv_state->external_port;
    action_state->touch = recv_state->last_pkt_time;
    action_state->cxid = recv_state->cxid;
    uint32_t hash = recv_state->hash;
    action_state->hash = hash;
    uint32_t nat_hash = recv_state->nat_hash;
    action_state->nat_hash = nat_hash;
    

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

    pthread_mutex_unlock(&ActionEntryLock);
    
  
    return 1;
}



int local_conn_get_one_perflow(connState* conn_state){	
	printf("local get conn one per flow\n");
	ConnState* conn_perflow = (ConnState*)malloc(sizeof(ConnState));
	conn_state__init(conn_perflow);

	conn_perflow->n_ether_src = 6;
        conn_perflow->ether_src = malloc(sizeof(uint32_t)*6);

        int m;

	for(m = 0; m < 6; m++){
		conn_perflow->ether_src[m]=conn_state->internal_mac[m];
	}
   

	conn_perflow->has_s_ip = 1;
	conn_perflow->s_ip = conn_state->internal_ip;
	conn_perflow->has_d_ip = 1;
	conn_perflow->d_ip = conn_state->external_ip;
	conn_perflow->has_s_port = 1;
        conn_perflow->s_port = conn_state->internal_port;
	conn_perflow->has_proto=1;
	conn_perflow->proto = conn_state->proto;
	int hash = conn_state->hash;			
	conn_perflow->has_hash=1;
	conn_perflow->hash = hash;
	int nat_hash = conn_state->nat_hash;			
	conn_perflow->has_nat_hash=1;
	conn_perflow->nat_hash = nat_hash;
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
	printf("local get one conn per flow---send successful\n");
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
		if(action_state->cxid != cxid){
			printf("get one action cxid middle\n ");
			action_state = action_state->next;
			continue;
		}

		ActionState* action_perflow = (ActionState*)malloc(sizeof(ActionState));;
		action_state__init(action_perflow);

        	
		action_perflow->has_last_pkt_time=1;
		action_perflow->last_pkt_time = action_state->touch;

		action_perflow->has_external_ip=1;
		action_perflow->external_ip = action_state->external_ip;
		action_perflow->has_external_port=1;
		action_perflow->external_port = action_state->external_port;

		action_perflow->has_cxid=1;
		action_perflow->cxid = action_state->cxid;		
		action_perflow->has_hash = 1;
		action_perflow->hash = action_state->hash;
		action_perflow->has_nat_hash = 1;
		action_perflow->nat_hash = action_state->nat_hash;
		
		MyActionMessage mes;
        	my_action_message__init(&mes);	
        	mes.data_type = MY_ACTION_MESSAGE__DATA_TYPE__ActionStateType;
        	mes.message_case = MY_ACTION_MESSAGE__MESSAGE_ACTION_STATE;
        	mes.actionstate = action_perflow;
 
        	int len = my_action_message__get_packed_size(&mes);
        	void *buf = malloc(len);
        	my_action_message__pack(&mes, buf);

		int result = action_send_perflow(buf, len);    
       		 if(result < 0){
			return -1;
		}
		action_state = action_state->next;
	        printf("local get one action per flow ---send successful\n");
		
		break;
		
	}


	pthread_mutex_unlock(&ActionEntryLock);
	//printf("local get one action per flow ---unlock\n");
	free(match);
	return 1;
}





static void *conn_sender(void *arg){
	//printf("start a conn sender\n");
	
	connState* conn_state = (connState*)arg;
	int send_conn = local_conn_get_one_perflow(conn_state);
	if(send_conn < 0){
		printf("send failed");
	}

	
}

static void *action_sender(void *arg){
	printf("start a action sender\n");
	Match *match = (Match*)arg;
	
	printf("match hash %d\n", match->hash);
	printf("match cxid %d\n", match->cxid);
	int send_action = local_action_get_one_perflow(match);
	if(send_action < 0){
		printf("send failed");
	}

}

int local_conn_get_perflow(Key key){
     printf("start conn get perflow\n");
     //printf("local  key.dl_type %x\n", key.dl_type);
     //printf("key.nw_proto %u\n",key.nw_proto);
 
    int count = 0;
    int h = 0;
    for (h = 0; h < BUCKET_SIZE; h++)
    {        
        pthread_mutex_lock(&ConnEntryLock);
        connState *conn_state = conn_bucket[h];
        while (conn_state != NULL)
        {

		
		//if(count == 1){
		//	printf("count == 1\n");
		//	return 1; 
		//}

		//printf("local key.wildcards & WILDCARD_DL_TYPE %d\n", key.wildcards & WILDCARD_DL_TYPE);
		//printf("local key.wildcards & WILDCARD_NW_PROTO %d\n", key.wildcards & WILDCARD_NW_PROTO);
		//printf("localconn_head[i]->hw_proto %u\n", conn_state->hw_proto);
		//printf("localconn_head[i]->hw_proto %u\n",ntohs(key.dl_type));
		//printf("ntohs(key.dl_type) %x\n", conn_state->proto);
		
		            // Check nw_proto
		if ((!(key.wildcards & WILDCARD_NW_PROTO)) &&((conn_state->proto) != key.nw_proto))
			{
		                conn_state = conn_state->next;
		                continue;
		        }


		/*int send_conn = local_conn_get_one_perflow(conn_state);
		if(send_conn < 0){
			printf("send failed");
		}

		
		int send_action = local_action_get_one_perflow(match);
		if(send_action < 0){
			printf("send failed");
		}*/
	    
	  
	       	

		
	    int err;
	     if((err = pthread_create(&conn_thread, NULL, conn_sender, (void*)conn_state))!=0)
             {
             	perror("pthread_create error");
             }
	     

	     printf("ad_nat_firewall %d",ad_nat_firewall);
	     if(ad_nat_firewall == 0){	 
 		
    
	     	Match* match = (Match*)malloc(sizeof(Match));
	     	match->hash = conn_state->hash;
	     	match->cxid = conn_state->cxid;
		
	     	//create a thread to send action state
	     	if((err = pthread_create(&action_thread, NULL, action_sender, (void*)match))!=0)
             	{
                	 perror("pthread_create error");
             	}
		
	      }
	 	
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
    struct in6_addr ips;
    struct in6_addr ipd;

    ips.s6_addr32[0] = conn_state->internal_ip;
    ipd.s6_addr32[0] = conn_state->external_ip;

    //struct sockaddr_in sa;
    char src_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(ips), src_str, INET_ADDRSTRLEN);
   
    //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(ipd), dst_str, INET_ADDRSTRLEN);
    


    printf("---------------ConnState------------------\n");

    printf("src_ip %s\n", src_str);
    printf("dst_ip %s\n", dst_str);
    printf("internal_port %u\n",conn_state->internal_port);
    printf("mac_src %u",conn_state->internal_mac[0]);
    printf(" %u",conn_state->internal_mac[1]);
    printf(" %u",conn_state->internal_mac[2]);
    printf(" %u",conn_state->internal_mac[3]);
    printf(" %u",conn_state->internal_mac[4]);
    printf(" %u\n",conn_state->internal_mac[5]);
    printf("cxid  %d\n",conn_state->cxid);
    printf("hash  %d\n",conn_state->hash);
    printf("---------------ConnState------------------\n");

}

//+++

//+++
void showActionState(actionState* action_state){

    struct in6_addr ipd;

    ipd.s6_addr32[0] = action_state->external_ip;

   //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(ipd), dst_str, INET_ADDRSTRLEN);


    printf("---------------actionState------------------\n");
    printf("ds_ip %s\n", dst_str);
    printf("external_port %u\n",action_state->external_port);
    printf("last_pkt_time %lu\n", action_state->touch);
    printf("cxid: %d\n",action_state->cxid);
    printf("hash  %d\n",action_state->hash);
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
            //showConnState(conn_state); 
            //conn[count_conn] = conn_state->cxid; 
	    conn[count_conn] = conn_state->hash;
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }   
	while (action_state != NULL)
        {     
            printf("-----------action---h%d------------\n",h);
	    //showActionState(action_state); 
            //action[count_action] = action_state->cxid; 
            action[count_action] = action_state->hash;
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }             
    }
    printf("\n");
    int m,n;
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



/**
 * Print each records of the natting table
 *
 * @param mode Verbosity level (see enum print_mode)
 */
void table_print(enum print_mode mode)
{
    int iter;
 
    if (mode == PRINT_ALL)
        printf("     internal MAC |");

    printf("  internal IP | in. port | ex. port |   external IP");

    if (mode == PRINT_ALL)
        printf(" | touch");

    printf("\n");

    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        connState *conn_record = conn_bucket[iter];
	actionState *action_record = action_bucket[iter];

	if(conn_record != NULL){
		printf("conn_record iter %d",iter);
	}


        while (conn_record) {
            if (mode == PRINT_ALL){
            	printf("%17s |",
                    ether_ntoa((struct ether_addr *)&(conn_record->internal_mac)));

        	printf("%13s | %8u | ",
                    	inet_ntoa(*(struct in_addr *)&(conn_record->internal_ip)),
                	conn_record->internal_port);
        	printf("%8u | %13s",
                	action_record->external_port,
                	inet_ntoa(*(struct in_addr *)&(action_record->external_ip)));
	    }
            if (mode == PRINT_ALL)
            	printf(" | %lu", (long unsigned)action_record->touch);
	    
            printf("iter %d\n",iter); 
	    conn_record = conn_record->prev;
	    action_record = action_record->prev;
        } // end while cxt 
    } // end for buckets


    printf("\n");
}


/**
 * Get the mapped external port for a record
 *
 * @param internal_ip   The internal IP address
 * @param internal_port The internal port
 * @param external_ip   The external IP address
 * @return The mapped port (or 0 if not found)
 */
uint16_t table_get_external_port(uint32_t hash, uint32_t cxid)
{
    //printf("able_get_external_port\n");
    uint16_t external_port = 0;
    actionState *action_record;
    do {
        external_port = (hash+cxid) % (MAX_EXTERNAL_PORT - MIN_EXTERNAL_PORT)
            + MIN_EXTERNAL_PORT;
        for (action_record = action_bucket[hash]; action_record && action_record->external_port != external_port;
                action_record = action_record->next);
    } while (action_record);

    return external_port;
}

/**
 * Adds a record in the table
 *
 * @param internal_ip   The internal IP address
 * @param internal_mac  The internal MAC address
 * @param internal_port The internal port
 * @param external_ip   The external IP address
 * @return The new added record (beginning of the table)
 */
connState *conn_table_add(uint32_t internal_ip, uint8_t *internal_mac,
        uint16_t internal_port, uint32_t external_ip, uint32_t hash, packetinfo* pi)
{
    //printf("Creating conn table\n");
    cxtrackerid++;

//+++
    connac_notify_flow_created();
//+++

    connState *record;

    if ((record = (connState *)malloc(sizeof(connState)))== NULL) {
        perror("Unable to allocate a new record");
        return NULL;
    }

    memcpy(record->internal_mac, internal_mac, ETH_ALEN); /* broadcast */
    record->internal_ip = internal_ip;
    record->internal_port = internal_port;

    record->external_ip = external_ip;
    record->hash = hash;
    record->cxid = cxtrackerid;
    record->proto = pi->ip->protocol;

    pi->cxid = cxtrackerid;

    connState* head;
    head = conn_bucket[hash];

    /* * New connections are pushed on to the head of bucket[s_hash] */
    record->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = record;
    }
    conn_bucket[hash] = record;
   
    return record;
}

/**
 * Adds a record in the table
 *
 * @param internal_ip   The internal IP address
 * @param internal_mac  The internal MAC address
 * @param internal_port The internal port
 * @param external_ip   The external IP address
 * @return The new added record (beginning of the table)
 */
actionState *action_table_add(uint32_t hash, uint32_t cxid, packetinfo* pi)
{
    //printf("Creating action table\n");
    actionState *record;

    if ((record = (actionState *)malloc(sizeof(actionState)))== NULL) {
        perror("Unable to allocate a new record");
        return NULL;
    }

    record->external_port = table_get_external_port(hash, cxid);
    
    record->external_ip = pi->ip->daddr;
    record->touch = time(NULL); /* current timestamp */
    record->hash = hash;
    record->cxid = cxid;

    actionState* head;
    head = action_bucket[hash];

    /* * New connections are pushed on to the head of bucket[s_hash] */
    record->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = record;
    }
    action_bucket[hash] = record;
   
    return record;
}

/*
void remove_state_node(table_record * record, table_record ** bucket_ptr)
{
    //printf("remove-state-node function\n");
    table_record * prev = record->prev;       // OLDER connections 
    table_record * next = record->next;       // NEWER connections 

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

    
    //Free and set to NULL 
    
    free(record);
    record = NULL;
}

void remove_hash_node(table_record * record, int hash)
{
	//printf("remove-hash-node function\n");
	// remove from the hash 
        if (record->prev)
        	record->prev->next = record->next;
        if (record->next)
        	record->next->prev = record->prev;
        table_record *tmp = record;

        record = record->prev;

        remove_state_node(tmp, &bucket[hash]);
	if (record == NULL) {
        	bucket[hash] = NULL;
        }

}

void state_expunge_expired()
{
    //printf("state_expunge_expired function\n");
    time_t current = time(NULL);
    table_record * record;
    int iter;


    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        record = bucket[iter];
        while (record != NULL) {
            if (difftime(record->touch, current) > RECORD_TIMEOUT) {
                remove_hash_node(record, iter);
            } else {
                record = record->prev;
            }
        } // end while cxt
    } // end for buckets
}

*/
/**
 * Proccess an outcomming packet and delete old records
 *
 * @param internal_ip   The internal IP address
 * @param internal_mac  The internal MAC address
 * @param internal_port The internal port
 * @param external_ip   The external IP address
 * @return The corresponding record
 */
connState* conn_table_outbound(packetinfo* pi)
{

    //printf("conn table_outbound\n");
    u_int16_t src_port, dst_port;
    uint32_t internal_ip;
    uint8_t *internal_mac;
    uint16_t internal_port;
    uint32_t external_ip;
    uint32_t hash;

    src_port = pi->src_port;
    dst_port = pi->dst_port;

    internal_ip = pi->ip->saddr;
    internal_mac = pi->eth->h_source;

    internal_port = src_port;
    external_ip = pi->ip->daddr;
    hash= pi->hash;


    connState *record;
    record = conn_bucket[hash];

    while (record) {
        if (record->internal_ip == internal_ip &&
                record->internal_port == internal_port &&
                record->external_ip == external_ip) {
	    pi->cxid = record->cxid;
            return record;
        }
	record = record->next;
    }

    record = conn_table_add(internal_ip, internal_mac, internal_port, external_ip, hash, pi);
    return record;
}

/**
 * Proccess an outcomming packet and delete old records
 *
 * @param internal_ip   The internal IP address
 * @param internal_mac  The internal MAC address
 * @param internal_port The internal port
 * @param external_ip   The external IP address
 * @return The corresponding record
 */
actionState *action_table_outbound(packetinfo* pi)
{
    //printf("action table_outbound\n");
    uint32_t hash;
    hash= pi->hash;
    
    uint32_t cxid;
    cxid= pi->cxid;
   
    actionState *record = action_bucket[hash];
 
    while (record) {
        if (record->cxid == cxid) {
            record->touch = time(NULL); /* touch! */
            return record;
        }
	record = record->next;
    }

    record = action_table_add(hash,cxid, pi);
    return record;
}


/**
 * Proccess an incomming packet
 *
 * @param external_ip   The external IP address
 * @param external_port The external port
 * @return The corresponding record
 */

//inbound table must be reversed,use action_nat_bucket to find a match hash
//use conn_nat_bucket to do the real action  
int conn_table_inbound(packetinfo* pi)
{
    //printf("nat conn table inbound---------------\n");
    uint32_t external_ip = pi->ip->saddr;
    uint16_t external_port = pi->dst_port;
  
    uint32_t hash = hash_nat_array[pi->nat_hash];
    actionState *record = action_bucket[hash];  

    while (record) {
        //printf("record :%8u | %13s \n", record->external_port, inet_ntoa(*(struct in_addr *)&(record->external_ip)));       
        //printf("parameters :%8u | %13s \n",external_port, inet_ntoa(*(struct in_addr *)&(external_ip)));

        if (record->external_ip == external_ip &&
                record->external_port == external_port ) {
	    pi->cxid = record->cxid;
	    record->touch = time(NULL); /* touch! */
	    //printf("find record\n");
            return 1;
        }
	record = record->next;
    }

#ifdef DEBUG
    fprintf(stderr, 
            "Warning: incomming packet from unknown tuple (IP, port)\n");
#endif
    return 0; /* packet should be ignored or returned to sender */
}


/**
 * Proccess an incomming packet
 *
 * @param external_ip   The external IP address
 * @param external_port The external port
 * @return The corresponding record
 */

connState *action_table_inbound(packetinfo* pi)
{
    //printf("nat action table inbound---------------\n");
    uint32_t hash = hash_nat_array[pi->nat_hash];
    connState *record = conn_bucket[pi->nat_hash];

    while (record) {
        if (record->cxid == pi->cxid) {
	    //printf("find record\n");
        }
	record = record->next;
    }

#ifdef DEBUG
    fprintf(stderr, 
            "Warning: incomming packet from unknown tuple (IP, port)\n");
#endif
    return NULL; /* packet should be ignored or returned to sender */
}




