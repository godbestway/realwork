#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNACProto_H_
#define _CONNACProto_H_

#include <pcap.h>
#include <stdint.h>
#include "CONNAC.h"

///// DEFINES ////////////////////////////////////////////////////////////////
#define PROTO_PERSON	0
#define PROTO_INFORMATION	1
#define PROTO_SYN	2
#define PROTO_GETPERFLOWMSG	3


///// STRUCTS ///////////////////////////////////////////////////////////////





///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//json_object *json_compose_perflow_key(PerflowKey *key)

//json_object* json_compose_discover();

int send_proto_object(int conn, ProtoObject* proto_object);
ProtoObject* proto_compose_person_message(char* name, int age, char* address);
ProtoObject* proto_compose_information_message(int personnum, char* content);
ProtoObject* proto_compose_syn_message();

#endif

#ifdef __cplusplus
}
#endif
