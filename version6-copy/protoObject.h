#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNACProto_H_
#define _CONNACProto_H_

#include <pcap.h>
#include <stdint.h>
#include "CONNAC.h"

///// DEFINES ////////////////////////////////////////////////////////////////
///// STRUCTS ///////////////////////////////////////////////////////////////


extern pthread_mutex_t connac_lock_conn;
extern pthread_mutex_t connac_lock_action;
///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//json_object *json_compose_perflow_key(PerflowKey *key)

//json_object* json_compose_discover();

int send_conn_proto_object(int conn, uint8_t* buf, int len );
int send_action_proto_object(int conn, uint8_t* buf, int len );
int send_conn_syn_message(int conn);
int send_action_syn_message(int conn);

/*ProtoObject* proto_compose_person_message(char* name, int age, char* address);
ProtoObject* proto_compose_conn_putPerflowack_message(int hash);
ProtoObject* proto_compose_action_putPerflowack_message(int hash);
ProtoObject* proto_compose_conn_getPerflowack_message(int count);
ProtoObject* proto_compose_action_getPerflowack_message(int count);
ProtoObject* proto_compose_syn_message();
*/
#endif

#ifdef __cplusplus
}
#endif
