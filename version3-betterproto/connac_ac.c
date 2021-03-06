#include "CONNAC.h"
#include "connac_ac.h"
#include "debug.h"
#include "protoObject.h"
#include "myActionMessage.pb-c.h"

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
int connac_action_state = -1;


int action_send_getPerflowAck(int count){
        printf("send action getPerflowAck\n");

	ActionGetPerflowAckMsg	actionGetPerflowAckMsg;
	action_get_perflow_ack_msg__init(&actionGetPerflowAckMsg);

        actionGetPerflowAckMsg.has_count=1;
	actionGetPerflowAckMsg.count = count;
	MyActionMessage mes;
        my_action_message__init(&mes);
   
        mes.data_type = MY_ACTION_MESSAGE__DATA_TYPE__ActionGetPerflowAckMsgType;
        mes.message_case = MY_ACTION_MESSAGE__MESSAGE_ACTION_GET_PERFLOW_ACK_MSG;
        mes.actiongetperflowackmsg = &actionGetPerflowAckMsg;
 
        int len = my_action_message__get_packed_size(&mes);
        printf("size of getPerflowAck : %u\n", len);
        void *buf = malloc(len);
        my_action_message__pack(&mes, buf);

	int result;
	result = send_conn_proto_object(connac_action_state, buf, len );
	if(result < 0){
		return -1;
	}


	return result;

}

int action_send_putPerflowAck(int hash, int cxid){
	printf("send action putPerflowAck\n");

	ActionPutPerflowAckMsg	actionPutPerflowAckMsg;
	action_put_perflow_ack_msg__init(&actionPutPerflowAckMsg);

        actionPutPerflowAckMsg.has_hash=1;
	actionPutPerflowAckMsg.hash = hash;
	actionPutPerflowAckMsg.has_cxid=1;
	actionPutPerflowAckMsg.cxid = cxid;

	MyActionMessage mes;
        my_action_message__init(&mes);
   
        mes.data_type = MY_ACTION_MESSAGE__DATA_TYPE__ActionPutPerflowAckMsgType;
        mes.message_case = MY_ACTION_MESSAGE__MESSAGE_ACTION_PUT_PERFLOW_ACK_MSG;
        mes.actionputperflowackmsg = &actionPutPerflowAckMsg;
 
        int len = my_action_message__get_packed_size(&mes);
        printf("size of getPerflowAck : %u\n", len);
        void *buf = malloc(len);
        my_action_message__pack(&mes, buf);

	int result;
	result = send_conn_proto_object(connac_action_state, buf, len );
	if(result < 0){
		return -1;
	}

	return result;
}

int action_send_perflow(uint8_t* buf, int len){
	int result;
	result = send_conn_proto_object(connac_action_state, buf, len );
	if(result < 0){
		return -1;
	}
	return result;
}



static int handle_get_perflow(ActionGetPerflowMsg* actionGetPerflow_recv)
{
    if (NULL == connac_locals->action_get_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }

    int count;
    Key key;
    if(actionGetPerflow_recv->has_hw_proto){
	key.dl_type = actionGetPerflow_recv->hw_proto;
	printf("handle get perflow hw_proto %x\n",key.dl_type);
	}
    else{ key.wildcards |= WILDCARD_DL_TYPE;  }
    if(actionGetPerflow_recv->has_proto){
	key.nw_proto = actionGetPerflow_recv->proto;
	printf("handle get perflow proto %u\n",key.nw_proto);
	}
    else{  key.wildcards |= WILDCARD_NW_PROTO; }



    pthread_mutex_lock(&connac_action_lock_get);

    INFO_PRINT("receive getPerflow msg and try to get states");
    count = connac_locals->action_get_perflow(key);
    printf("perflow count %d",count);
    action_send_getPerflowAck(count);    

    pthread_mutex_unlock(&connac_action_lock_get);


}


static int handle_put_perflow(ActionPutPerflowMsg* actionPutPerflow_recv)
{
    if (NULL == connac_locals->action_put_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }

    ActionState* state = actionPutPerflow_recv->state;
    printf("state count\n");
    connac_locals->action_put_perflow(state);
    int32_t hash = state->hash;
    printf("state->hash %u \n",hash);
    uint64_t cxid = state->cxid;
    printf("state->cxid %lu\n",cxid);
    action_send_putPerflowAck(state->hash, state->cxid);
}


static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    while (1)
    {
        INFO_PRINT("while.....action....\n");        
	// Attempt to read a JSON string


	ProtoObject protoObject;

        protoObject = action_read(connac_action_state);

	MyActionMessage myActionMessage = *my_action_message__unpack(NULL,protoObject.length,protoObject.object);




        INFO_PRINT("while...connread...finish...\n");

	int data_type = myActionMessage.data_type;
        printf("data_type : %d\n",data_type );


        //printf("MY_MESSAGE__DATA_TYPE__ActionGetPerflowMsgType: %d", MY_MESSAGE__DATA_TYPE__ActionGetPerflowMsgType);
	//try put len on first position
        //force translation from char to uint_8
 	
	
	if(myActionMessage.data_type == MY_ACTION_MESSAGE__DATA_TYPE__ActionGetPerflowMsgType){
		ActionGetPerflowMsg* actionGetPerflowMsg = myActionMessage.actiongetperflowmsg;
		handle_get_perflow(actionGetPerflowMsg);

	}else if(myActionMessage.data_type ==MY_ACTION_MESSAGE__DATA_TYPE__ActionPutPerflowMsgType){
		ActionPutPerflowMsg* actionPutPerflowMsg = myActionMessage.actionputperflowmsg;
		handle_put_perflow(actionPutPerflowMsg);

	}else{ 
            ERROR_PRINT("Unknown type!!!!!");
        }
        
	
	

        // Get message type
        
            

        // Free JSON object
        
    }

    INFO_PRINT("State handling thread finished");
    pthread_exit(NULL);
}



int action_init()
{
    // Open state communication channel
    connac_action_state = conn_active_open(connac_config.ctrl_ip, 
            connac_config.ctrl_port_action);
    if (connac_action_state < 0)
    { 
        ERROR_PRINT("Failed to open state communication channel");
        return connac_action_state; 
    }
   

    int send_success = send_action_syn_message(connac_action_state);
    if(send_success < 0){
	INFO_PRINT("send message failed");
	return -1;
     }
    

    // Create SDMBN state handling thread
    pthread_create(&state_thread, NULL, state_handler, NULL);
    return 1;
}

int action_cleanup()
{
    // Close state communication channel
    if (conn_close(connac_action_state) >= 0)
    { connac_action_state = -1; }
    else
    { ERROR_PRINT("Failed to close state communication channel"); }

    // Destroy state thread
    //pthread_kill(state_thread, SIGKILL);

    return 1;
}
