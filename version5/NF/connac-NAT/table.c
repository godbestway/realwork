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


extern connState *nat_conn_bucket[BUCKET_SIZE];
extern actionState *nat_action_bucket[BUCKET_SIZE];
connState *conn_bucket[BUCKET_SIZE];
actionState *action_bucket[BUCKET_SIZE];
uint32_t cxid = 0;


/**
 * Print each records of the natting table
 *
 * @param mode Verbosity level (see enum print_mode)
 */
void table_print(enum print_mode mode)
{
    connState *conn_record;
    actionState *action_record;
    int iter;
 
    if (mode == PRINT_ALL)
        printf("     internal MAC |");

    printf("  internal IP | in. port | ex. port |   external IP");

    if (mode == PRINT_ALL)
        printf(" | touch");

    printf("\n");

    for (iter = 0; iter < BUCKET_SIZE; iter++) {
	if(conn_record != NULL){
		printf(" conn_record != NULL");
	}

        conn_record = conn_bucket[iter];
	action_record = action_bucket[iter];
        while (conn_record != NULL) {
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

            printf("\n");
	    conn_record = conn_record->prev;
	    action_record = action_record->prev;
        } // end while cxt
    } // end for buckets


    printf("\n");
}

void table_hash_print(uint32_t hash)
{
    connState *conn_record;
    //actionState *action_record;
   //printf("outbound hash %d\n",hash);
        conn_record = conn_bucket[hash];
        //printf(" conn_record = conn_bucket[hash];\n");


	//action_record = action_bucket[hash];
        //printf(" conn_record = conn_bucket[hash];\n");
        if(conn_record != NULL){
		printf(" conn_record != NULL");
	}
	else{printf(" conn_record == NULL\n"); }



        while (conn_record != NULL) {
		//printf(" conn_record != NULL  !!!!!!");

                //if(conn_record->internal_mac != NULL){
		//	printf(" conn_record->internal_mac != NULL");
		//}
		//else{
		//	printf(" conn_record->internal_mac == NULL");
		//}
		

            	printf("%17s |",
                    ether_ntoa((struct ether_addr *)&(conn_record->internal_mac)));

        	printf("%13s | %8u | ",
                    	inet_ntoa(*(struct in_addr *)&(conn_record->internal_ip)),
                	conn_record->internal_port);
        	//printf("%8u | %13s",
                //	action_record->external_port,
                //	inet_ntoa(*(struct in_addr *)&(action_record->external_ip)));
	    
            
            	//printf(" | %lu", (long unsigned)action_record->touch);

            printf("\n");
	    conn_record = conn_record->prev;
	    //action_record = action_record->prev;
        } // end while cxt
    


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
uint16_t table_get_external_port(uint32_t hash)
{
    uint16_t external_port = 0;
    actionState *action_record;

    srand(time(NULL));

    do {
        external_port = rand() % (MAX_EXTERNAL_PORT - MIN_EXTERNAL_PORT)
            + MIN_EXTERNAL_PORT;
        for (action_record = action_bucket[hash]; action_record && action_record->external_port != external_port;
                action_record = action_record->prev);
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
    cxid++;
    //printf("flow_number %d\n",cxid);

    connState *record;

    if ((record = (connState *)malloc(sizeof(connState)))== NULL) {
        perror("Unable to allocate a new record");
        return NULL;
    }

    memcpy(record->internal_mac, internal_mac, ETH_ALEN); /* broadcast */
    record->internal_ip = internal_ip;
    record->internal_port = internal_port;
    //printf("record->internal_port %u\n",record->internal_port);

    record->external_ip = external_ip;
    record->proto = pi->ip->protocol;
    record->hash = hash;
    record->cxid = cxid;
    pi->cxid = cxid;

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

    record->external_port = table_get_external_port(hash);
    //printf("record->external_port %u\n",record->external_port);
    
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

    //printf("table_outbound\n");
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
    //printf("outbound internal_port %d\n",internal_port);

    
    external_ip = pi->ip->daddr;

    hash= pi->hash;
    //printf("outbound hash %d\n",hash);

    connState *record;
    record = conn_bucket[hash];
    //table_record *before = NULL;

    while (record) {
        if (record->internal_ip == internal_ip &&
                record->internal_port == internal_port &&
                record->external_ip == external_ip) {
	    pi->cxid = record->cxid;
            return record;
        }
        record = record->prev;
    }

    //printf("table out bound finish\n");
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

    uint32_t hash;
    hash= pi->hash;
    //printf("outbound hash %d\n",hash);

    uint32_t cxid;
    cxid= pi->cxid;
    //printf("outbound cxid %d\n",cxid);
	
    actionState *record = action_bucket[hash];
    //table_record *before = NULL;

    while (record) {
        if (record->cxid == cxid) {
            record->touch = time(NULL); /* touch! */
            return record;
        }

        record = record->prev;
    }

    record = action_table_add(hash,cxid, pi);

    //printf("action table outbound final finish\n");
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
  
    actionState *record = nat_action_bucket[pi->hash];

    //printf("hash %d\n",pi->hash);
    //if(record == NULL){
    //	printf("record == NULL\n");
    //}

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
        record = record->prev;
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
    connState *record =nat_conn_bucket[pi->hash];

    //printf("hash %d\n",pi->hash);
    //if(record == NULL){
    //	printf("record == NULL\n");
    //}

    while (record) {
        if (record->cxid == pi->cxid) {
	    //printf("find record\n");
            return record;
        }
        record = record->prev;
    }

#ifdef DEBUG
    fprintf(stderr, 
            "Warning: incomming packet from unknown tuple (IP, port)\n");
#endif
    return NULL; /* packet should be ignored or returned to sender */
}




