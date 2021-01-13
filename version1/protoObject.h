#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SDMBNJson_H_
#define _SDMBNJson_H_

#include <pcap.h>
#include <stdint.h>


///// DEFINES ////////////////////////////////////////////////////////////////
#define PROTO_PERSON	0
#define PROTO_INFORMATION	1
#define PROTO_SYN	2
#define PROTO_GETPERFLOWMSG	3


///// STRUCTS ///////////////////////////////////////////////////////////////

typedef struct{
	int length;		//send_protoObject need a message length for coding head
	uint8_t* buf;
	uint8_t message_type;	//send_protoObject need a message type for coding head
	
}ProtoObject;



///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//json_object *json_compose_perflow_key(PerflowKey *key)

//json_object* json_compose_discover();
int send_proto_object(int conn, ProtoObject * proto_object);
ProtoObject* proto_compose_person_message(char* name, int age, char* address);
ProtoObject* proto_compose_information_message(int personnum, char* content);
ProtoObject* proto_compose_syn_message();

#endif

#ifdef __cplusplus
}
#endif
