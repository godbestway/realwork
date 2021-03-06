#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNAC_H_
#define _CONNAC_H_

#include "ActionState.pb-c.h"
#include "ConnState.pb-c.h"
#include <stdint.h>
#include <sys/time.h>
#include <pcap/pcap.h>


typedef struct {
	uint32_t nw_src;
	uint32_t nw_src_mask;
	uint32_t nw_dst;
	uint32_t nw_dst_mask;
	uint16_t tp_src;
	uint16_t tp_dst;
    uint16_t dl_type;
	uint8_t nw_proto;
    uint8_t wildcards;
	uint8_t tp_flip;
} PerflowKey;

typedef struct{
	int length;		//send_protoObject need a message length for coding head
	uint8_t* buf;
	uint8_t message_type;	//send_protoObject need a message type for coding head
	
}ProtoObject;


#define WILDCARD_DL_TYPE    0x01
#define WILDCARD_NW_SRC     0x02
#define WILDCARD_NW_DST     0x04
#define WILDCARD_NW_PROTO   0x08
#define WILDCARD_TP_SRC     0x10
#define WILDCARD_TP_DST     0x20
#define WILDCARD_NW_SRC_MASK    0x40
#define WILDCARD_NW_DST_MASK    0x80
#define WILDCARD_NONE       0x00
#define WILDCARD_ALL        0xFF

#define PROTO_CONNPERFLOW 0x11;	
#define PROTO_ACTIONPERFLOW 0x12;
#define PROTO_ACTIONMULTIFLOW 0x13;
#define PROTO_ACTIONALLFLOW 0x14;		

//NF should provide
typedef struct {
    //int (*init)();
    //int (*cleanup)();
    int (*conn_get_perflow)();
    int (*conn_put_perflow)(ConnState* state); 
    int (*action_get_perflow)();
    int (*action_put_perflow)(ActionState* state); 
    
} CONNACLocals;

///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//shared library export

int conn_send_perflow(ProtoObject* proto_object);
int connac_init(CONNACLocals *locals);
int connac_cleanup();
int connac_send_perflow(ProtoObject * proto_object);
int action_send_perflow(ProtoObject * proto_object);

void connac_notify_packet_received(char *type, struct timeval *recv_time);
void connac_notify_flow_created();
void connac_notify_flow_destroyed();


#endif

#ifdef __cplusplus
}
#endif
