#include "CONNAC.h"
#include "conn.h"
#include "debug.h"
#include "information.pb-c.h"

/*#include "connPutPerflowAckMsg.pb-c.h"
#include "actionPutPerflowAckMsg.pb-c.h"
#include "connGetPerflowAckMsg.pb-c.h"
#include "actionGetPerflowAckMsg.pb-c.h"
#include "person.pb-c.h"
#include "syn.pb-c.h"*/
#include "protoObject.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <json/json.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pcap.h>
#include <stdint.h>


#define CONTENT_LEN 32
#define HEAD_LENGTH 4
static void writeRawVarint32(int conn, int value);

ProtoObject* make_proto_object(int len, uint8_t* buf, int message_type ){
	
	ProtoObject *proto_object;
    	proto_object = (ProtoObject *)malloc(sizeof(ProtoObject));	
	
	//printf("message %d\n",message_type);
	proto_object->length = len;
	proto_object->buf = buf;
	proto_object->message_type=message_type;

	return proto_object;
}

/*ProtoObject* proto_compose_syn_message(){
	Syn syn = SYN__INIT;

	int pid = getpid();
        char host[1024];
        memset(host, 0, 1024);
        gethostname(host, 1024);
        printf("hostname %s\n", host);
        printf("pid %d\n",pid);

    	syn.pid=pid;
    	syn.host = (char*)malloc(CONTENT_LEN);
    	syn.host=host;

    	//check info length  
    	unsigned int len;
    	len = syn__get_packed_size(&syn);
    	printf("send size of syn : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	syn__pack(&syn, buf);
	
	ProtoObject *syn_object;
    	syn_object = make_proto_object(len, buf,PROTO_SYN);	
	
	return syn_object;
	

}*/

int send_information_message(int conn, int personnum, char* content){
	Information info = INFORMATION__INIT;
    	info.personnum=personnum;
    	info.content = (char*)malloc(CONTENT_LEN);
    	info.content=content;

    	//check info length  
    	unsigned int len;
    	len = information__get_packed_size(&info);
    	printf("send size of info : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	information__pack(&info, buf);
	
	int result = send_proto_object(conn,buf, len );
	if(result < 0){
		printf("send failed");
		return -1;
	}

	free(buf);
	return result;
	

}

/*ProtoObject* proto_compose_person_message(char* name, int age, char* address){
	Person info = PERSON__INIT;
	info.name = (char*)malloc(CONTENT_LEN);
    	info.name=name;
    	info.age=age;
    	info.address = (char*)malloc(CONTENT_LEN);
    	info.address=address;

    	//check info length  
    	unsigned int len;
    	len = person__get_packed_size(&info);
    	printf("send size of info : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	person__pack(&info, buf);

	ProtoObject *person_object;
    	person_object = make_proto_object(len, buf,PROTO_PERSON);	
	
	return person_object;

}


ProtoObject* proto_compose_conn_getPerflowack_message(int count){
	ConnGetPerflowAckMsg connGetPerflowAck = CONN_GET_PERFLOW_ACK_MSG__INIT;
    	connGetPerflowAck.count=count;
    	
    	//check info length  
    	unsigned int len;
    	len = conn_get_perflow_ack_msg__get_packed_size(&connGetPerflowAck);
    	printf("send getPerflowAck size of : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	conn_get_perflow_ack_msg__pack(&connGetPerflowAck, buf);
	
	ProtoObject *connGetPerflowAck_object;
    	connGetPerflowAck_object = make_proto_object(len, buf, PROTO_CONN_GETPERFLOWMSGACK);	
	
	return connGetPerflowAck_object;
	

}

ProtoObject* proto_compose_action_getPerflowack_message(int count){
	ActionGetPerflowAckMsg actionGetPerflowAck = ACTION_GET_PERFLOW_ACK_MSG__INIT;
    	actionGetPerflowAck.count=count;
    	
    	//check info length  
    	unsigned int len;
    	len = action_get_perflow_ack_msg__get_packed_size(&actionGetPerflowAck);
    	printf("send getPerflowAck size of : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	action_get_perflow_ack_msg__pack(&actionGetPerflowAck, buf);
	
	ProtoObject *actionGetPerflowAck_object;
    	actionGetPerflowAck_object = make_proto_object(len, buf, PROTO_ACTION_GETPERFLOWMSGACK);	
	
	return actionGetPerflowAck_object;
	

}



ProtoObject* proto_compose_conn_putPerflowack_message(int hash){
	ConnPutPerflowAckMsg connPutPerflowAck = CONN_PUT_PERFLOW_ACK_MSG__INIT;
    	connPutPerflowAck.hash=hash;
    	
    	//check info length  
    	unsigned int len;
    	len = conn_put_perflow_ack_msg__get_packed_size(&connPutPerflowAck);
    	printf("send size of info : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	conn_put_perflow_ack_msg__pack(&connPutPerflowAck, buf);
	
	ProtoObject *connPutPerflowAck_object;
    	connPutPerflowAck_object = make_proto_object(len, buf, PROTO_CONN_PUTPERFLOWMSGACK);	
	
	return connPutPerflowAck_object;
	

}

ProtoObject* proto_compose_action_putPerflowack_message(int hash){
	ActionPutPerflowAckMsg actionPutPerflowAck = ACTION_PUT_PERFLOW_ACK_MSG__INIT;
    	actionPutPerflowAck.hash=hash;
    	
    	//check info length  
    	unsigned int len;
    	len = action_put_perflow_ack_msg__get_packed_size(&actionPutPerflowAck);
    	printf("send size of info : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	action_put_perflow_ack_msg__pack(&actionPutPerflowAck, buf);
	
	ProtoObject *actionPutPerflowAck_object;
    	actionPutPerflowAck_object = make_proto_object(len, buf, PROTO_ACTION_PUTPERFLOWMSGACK);	
	
	return actionPutPerflowAck_object;
	

}

*/

int send_proto_object(int conn, uint8_t* buf, int len ){
	
	if(buf == NULL){
		return -1;
	}

	writeRawVarint32(conn, len);
        

	int result = conn_write(conn, buf, len);
	if(result < 0){
		return -1;
	}
 	
		
	return result;
}


static void writeRawVarint32(int conn, int value) {
        char out;
	int result;
        while((value & -128) != 0) {
            out =value & 127 |128;
	    uint8_t out_while = (uint8_t)out;
	    
            result = conn_write(conn, &out_while, 1);
	    if(result < 0){
		printf("write wrong1\n");
		}
            value = value >>7;
           
        }
        uint8_t out_last = (uint8_t)value;
	result = conn_write(conn, &out_last, 1);
	if(result < 0){
		printf("write wrong2\n");
	}
}









	
