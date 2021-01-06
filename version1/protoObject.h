#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SDMBNJson_H_
#define _SDMBNJson_H_

#include <pcap.h>
#include <stdint.h>


///// DEFINES ////////////////////////////////////////////////////////////////
#define Proto_Person	0
#define Proto_Information	1


/*#define RESPONSE_DELETE_PERFLOW_ACK     "delete-perflow-ack"
#define EVENT_REPROCESS         "reprocess"
#define CONSTANT_ACTION_DROP            "drop"
#define ERROR_MALFORMED          "malformed"
*/

///// STRUCTS ///////////////////////////////////////////////////////////////

typedef struct{
	int length;
	uint8_t message_type;	
	uint8_t* buf;

}ProtoObject;



///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//json_object *json_compose_perflow_key(PerflowKey *key)

//json_object* json_compose_discover();
int send_proto_object(int conn, ProtoObject * proto_object);
ProtoObject* proto_compose_person_message(char* name, int age, char* address);
ProtoObject* proto_compose_information_message(int personnum, char* content);

#endif

#ifdef __cplusplus
}
#endif
