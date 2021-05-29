#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include "packets.h"
#include "rules.h"

#define BUCKET_SIZE  255
#define EXPIRE_STATE 60


#define CXT_HASH4(src,dst,sp,dp,pr) \
   (( src + dst + sp + dp + pr) % BUCKET_SIZE)



//OPEN=SYN, HALF=SYNACK, ESTABLISHED=ACK
//CLOSED=NOT in state table
typedef enum{OPEN, CLOSED} state_t;

//need to free ip_string when done with node

typedef struct _state_node {
    u_char src_ip[4];
    u_short src_prt;
    u_char dst_ip[4];
    u_short dst_prt;
    u_char proto;
    time_t time; //The last time this connection was active
    state_t state; //The current state of the node
//    char ip_string[50]; //The generated ip string
    int hash;
    struct _state_node* next;//The next state_node in the list
    struct _state_node* prev;//the rpevious node in the list
}state_node;



int get_hash(packetinfo *pi);
void append_to_list(state_node* sn);
void remove_state_node(state_node* sn, state_node ** bucket_ptr);
void remove_hash_node(state_node* sn, int hash);
void update_time(state_node* sn);
void state_expunge_expired();
state_node* create_node(packetinfo *pi);
rule_type_t process_with_conn_state(packetinfo *pi);
rule_type_t process_with_action_state(struct ip_header* h_ip, struct tcp_header* h_tcp);
state_node* find_state(packetinfo *pi);
void update_state(state_node* sn,state_t state );


/*END GLOBALS*/
#endif
