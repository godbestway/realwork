#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNAC_H_
#define _CONNAC_H_

//#include "ActionState.pb-c.h"
//#include "ConnState.pb-c.h"
#include "myConnMessage.pb-c.h"
#include "myActionMessage.pb-c.h"
#include <stdint.h>
#include <sys/time.h>
#include <pcap/pcap.h>


typedef struct {
        uint16_t dl_type;
	uint8_t nw_proto;
        uint8_t wildcards;
}Key;

typedef struct {
        uint32_t src_ip;
	uint32_t dst_ip;
	uint16_t src_port;
	uint16_t dst_port;	
	uint8_t nw_proto; 
}DirectKey;


#define WILDCARD_DL_TYPE    0x01
#define WILDCARD_NW_PROTO   0x08

//from connac_state.c
extern int drop;
extern int mode;
extern int share;
extern int ad_nat_firewall;
extern int get_conn;

//NF should provide
typedef struct {
    //int (*init)();
    //int (*cleanup)();
    int (*conn_get_perflow)(Key key);
    int (*conn_put_perflow)(ConnState* state);
    int (*action_get_perflow)(Key key);
    int (*action_put_perflow)(ActionState* state);
    
    int (*action_get_sharestate_perflow)(Key key);
    int (*action_put_sharestate_perflow)(ShareState* state);  

    int (*action_get_multiflow)(); 
    int (*action_put_multiflow)(ActionMultiState* state);
    int (*action_get_allflows)();
    int (*action_put_allflows)(ActionAllState* state);

    int (*action_get_direct_sharestate_perflow)(DirectKey key);  
    int (*action_get_direct_perflow)(DirectKey key);   
//+++
    int (*unlock_packet)();
//+++

    
} CONNACLocals;

///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//shared library export

int conn_send_perflow(uint8_t* buf, int len);
int action_send_perflow(uint8_t* buf, int len);
int connac_init(CONNACLocals *locals);
int connac_cleanup();

int sfc_send_putPerflowAck(ConnPutPerflowAckMsg connPutPerflowAckMsg);

void connac_notify_packet_received(char *type, struct timeval *recv_time);
void connac_notify_flow_created();
void connac_notify_flow_destroyed();


#endif

#ifdef __cplusplus
}
#endif
