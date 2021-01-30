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


int send_syn_message(int conn){


        printf("try to build a syn Message");
	Syn syn;
        syn__init(&syn);

	int pid = getpid();
        char host[1024];
        memset(host, 0, 1024);
        gethostname(host, 1024);
        printf("hostname %s\n", host);
        printf("pid %d\n",pid);

	syn.has_pid = 1;
    	syn.pid=pid;
    	syn.host = (char*)malloc(CONTENT_LEN);
    	syn.host=host;

        MyMessage mes;
        my_message__init(&mes);
   
        mes.data_type = MY_MESSAGE__DATA_TYPE__SynType;
        mes.message_case = MY_MESSAGE__MESSAGE_SYN;
        mes.syn = &syn;
 
        int len = my_message__get_packed_size(&mes);
        printf("size of MyMessage : %u\n", len);
        void *buf = malloc(len);
        my_message__pack(&mes, buf);

    	int result = send_proto_object(conn,buf, len );
	if(result < 0){
		printf("send failed");
		return -1;
	}

	free(buf);
	
	return result;
	

}



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









	
