#include "CONNAC.h"
#include "connac_state.h"
#include "connac_ac.h"
#include "debug.h"
#include "protoObject.h"
#include "myConnMessage.pb-c.h"

#include "connac_core.h"
#include "config.h"
#include "conn.h"

#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>



// Thread for handling state messages
static pthread_t state_thread;

// Connection for state messages
int connac_conn_state = -1;
int drop = 0;
int mode = 0;


int conn_send_getPerflowAck(int count){
        //printf("send conn getPerflowAck\n");

	ConnGetPerflowAckMsg	connGetPerflowAckMsg;
	conn_get_perflow_ack_msg__init(&connGetPerflowAckMsg);

        connGetPerflowAckMsg.has_count=1;
	connGetPerflowAckMsg.count = count;
	MyConnMessage mes;
        my_conn_message__init(&mes);
   
        mes.data_type = MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowAckMsgType;
        mes.message_case = MY_CONN_MESSAGE__MESSAGE_CONN_GET_PERFLOW_ACK_MSG;
        mes.conngetperflowackmsg = &connGetPerflowAckMsg;
 
        int len = my_conn_message__get_packed_size(&mes);
        //printf("size of getPerflowAck : %u\n", len);
        void *buf = malloc(len);
        my_conn_message__pack(&mes, buf);

	int result;
	result = send_conn_proto_object(connac_conn_state, buf, len );
	if(result < 0){
		return -1;
	}


	return result;

}

int sfc_send_putPerflowAck(ConnPutPerflowAckMsg connPutPerflowAckMsg){

	
	printf("sfc_send_putPerflowAck\n");
	MyConnMessage mes;
        my_conn_message__init(&mes);
   
        mes.data_type = MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowAckMsgType;
        mes.message_case =  MY_CONN_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_ACK_MSG;
        mes.connputperflowackmsg = &connPutPerflowAckMsg;

	printf("connPutPerflowAckMsg hash %u\n",mes.connputperflowackmsg->has_hash);
        printf("connPutPerflowAckMsg cxid %u\n",mes.connputperflowackmsg->has_cxid);
 
        int len = my_conn_message__get_packed_size(&mes);
        //printf("size of getPerflowAck : %u\n", len);
        void *buf = malloc(len);
        my_conn_message__pack(&mes, buf);

	int result;
	result = send_conn_proto_object(connac_conn_state, buf, len );
	if(result < 0){
		return -1;
	}

	return result;
}


int conn_send_putPerflowAck(ConnState* send_state){
	//printf("send conn putPerflowAck\n");

	ConnPutPerflowAckMsg connPutPerflowAckMsg;
	conn_put_perflow_ack_msg__init(&connPutPerflowAckMsg);

        connPutPerflowAckMsg.has_hash=1;
	connPutPerflowAckMsg.hash = send_state->hash;
	connPutPerflowAckMsg.has_cxid=1;
	connPutPerflowAckMsg.cxid = send_state->cxid;
	
	MyConnMessage mes;
        my_conn_message__init(&mes);
   
        mes.data_type = MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowAckMsgType;
        mes.message_case =  MY_CONN_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_ACK_MSG;
        mes.connputperflowackmsg = &connPutPerflowAckMsg;
 
        int len = my_conn_message__get_packed_size(&mes);
        //printf("size of getPerflowAck : %u\n", len);
        void *buf = malloc(len);
        my_conn_message__pack(&mes, buf);

	int result;
	result = send_conn_proto_object(connac_conn_state, buf, len );
	if(result < 0){
		return -1;
	}

	return result;
}

int conn_send_perflow(uint8_t* buf, int len){
	int result;
	result = send_conn_proto_object(connac_conn_state, buf, len );
	if(result < 0){
		return -1;
	}
	return result;
}



static int handle_get_perflow(ConnGetPerflowMsg* connGetPerflow_recv)
{
    if (NULL == connac_locals->conn_get_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }
//set drop flag == 1;
    drop = 1;
    int count;
    Key key;
    if(connGetPerflow_recv->has_hw_proto){
	key.dl_type = connGetPerflow_recv->hw_proto;
	printf("handle get perflow hw_proto %x\n",key.dl_type);
	}
    else{ key.wildcards |= WILDCARD_DL_TYPE;  }
    if(connGetPerflow_recv->has_proto){
	key.nw_proto = connGetPerflow_recv->proto;
	printf("handle get perflow proto %u\n",key.nw_proto);
	}
    else{  key.wildcards |= WILDCARD_NW_PROTO; }
    if(connGetPerflow_recv->has_mode){
	 mode = connGetPerflow_recv->mode;
	}


    pthread_mutex_lock(&connac_conn_lock_get);
 //   if(strcmp(key,"all")==0){
   // INFO_PRINT("receive getPerflow msg and try to get states");
    count = connac_locals->conn_get_perflow(key);
//	} 
   //printf("perflow count %d",count);
   conn_send_getPerflowAck(count);
   action_send_getPerflowAck(count);
   pthread_mutex_unlock(&connac_conn_lock_get);
}

static int handle_put_perflow(ConnPutPerflowMsg* connPutPerflow_recv)
{
    printf("handle_put_perflow\n");
    if (NULL == connac_locals->conn_put_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }

    ConnState* state = connPutPerflow_recv->state;
    //printf("state received");
    connac_locals->conn_put_perflow(state);

    //+++sfc support+++
    if(connac_config.ctrl_sfc == 0){
	conn_send_putPerflowAck(state);
    }
    

}

static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    while (1)
    {
        //INFO_PRINT("while....conn.....\n");        
	// Attempt to read a JSON string
	ProtoObject protoObject;

        protoObject = conn_read(connac_conn_state);

	MyConnMessage myConnMessage = *my_conn_message__unpack(NULL,protoObject.length,protoObject.object);

        printf(" myConnMessage type %d\n ", myConnMessage.data_type);
	
	 if(myConnMessage.data_type == MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowMsgType){
		ConnGetPerflowMsg* connGetPerflowMsg = myConnMessage.conngetperflowmsg;
		handle_get_perflow(connGetPerflowMsg);

	}else if(myConnMessage.data_type == MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowMsgType){
		printf("ConnPutPerflowMsgType received\n");
		ConnPutPerflowMsg *connPutPerflowMsg = myConnMessage.connputperflowmsg;
		handle_put_perflow(connPutPerflowMsg);

	}
	else if(myConnMessage.data_type == MY_CONN_MESSAGE__DATA_TYPE__UnlockMsgType){
		//printf("ConnPutPerflowMsgType received\n");
		UnlockMsg *unLockMsg = myConnMessage.unlockmsg;
		if (NULL == connac_locals->unlock_packet)
    		{
			printf("this function is not supported");
        		return -1; 
    		}
		connac_locals->unlock_packet();

	}else{ 
            ERROR_PRINT("Unknown type!!!!!");
        }

        
	
        
    }

    INFO_PRINT("State handling thread finished");
    pthread_exit(NULL);
}



int state_init()
{
    // Open state communication channel
    connac_conn_state = conn_active_open(connac_config.ctrl_ip, 
            connac_config.ctrl_port_conn);
    if (connac_conn_state < 0)
    { 
        ERROR_PRINT("Failed to open state communication channel");
        return connac_conn_state; 
    }
    printf("state init\n");


   	
    int send_success = send_conn_syn_message(connac_conn_state);
    
    if(send_success < 0){
	INFO_PRINT("send message failed");
	return -1;
     }
   
  
    // Create SDMBN state handling thread
    pthread_create(&state_thread, NULL, state_handler, NULL);
    return 1;
}

int state_cleanup()
{
    // Close state communication channel
    if (conn_close(connac_conn_state) >= 0)
    { connac_conn_state = -1; }
    else
    { ERROR_PRINT("Failed to close state communication channel"); }

    // Destroy state thread
    //pthread_kill(state_thread, SIGKILL);

    return 1;
}
