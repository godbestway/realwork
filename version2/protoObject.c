#include "CONNAC.h"
#include "conn.h"
#include "debug.h"
#include "information.pb-c.h"
#include "person.pb-c.h"
#include "protoObject.h"
#include "syn.pb-c.h"

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

ProtoObject* make_proto_object(int len, uint8_t* buf, int message_type ){
	
	ProtoObject *proto_object;
    	proto_object = (ProtoObject *)malloc(sizeof(ProtoObject));	
	
	//printf("message %d\n",message_type);
	proto_object->length = len;
	proto_object->buf = buf;
	proto_object->message_type=message_type;

	return proto_object;
}

ProtoObject* proto_compose_syn_message(){
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
	

}

ProtoObject* proto_compose_information_message(int personnum, char* content){
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
	
	ProtoObject *info_object;
    	info_object = make_proto_object(len, buf,PROTO_INFORMATION);	
	
	return info_object;
	

}

ProtoObject* proto_compose_person_message(char* name, int age, char* address){
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



int send_proto_object(int conn, ProtoObject* proto_object){
	
	uint8_t* buf = proto_object->buf;
	int len = proto_object->length;
	uint8_t type = proto_object->message_type;
	printf("type %x\n",type);

	if(buf == NULL){
		return -1;
	}

	//create a new buf, add prefix before info
    	uint8_t *new_buf = NULL;
	new_buf = (uint8_t*)malloc(len+HEAD_LENGTH);
    	new_buf[0] = len & 0xff;
    	new_buf[1] = (len>>8)&0xff;
    	new_buf[2] = 0;
    	new_buf[3] = type ;
   	 int m;
    	for(m = HEAD_LENGTH; m < len+HEAD_LENGTH; m++){
	new_buf[m] = buf[m-HEAD_LENGTH];
	}

	int result = conn_write(conn, new_buf, len+HEAD_LENGTH);

 	free(new_buf);
	return result;
}








	
