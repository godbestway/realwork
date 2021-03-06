#include "CONNAC.h"
#include "connac_ac.h"
#include "debug.h"
#include "protoObject.h"
#include "information.pb-c.h"
#include "actionPutPerflowAckMsg.pb-c.h"
#include "actionGetPerflowAckMsg.pb-c.h"
#include "actionPutPerflowMsg.pb-c.h"
#include "actionGetPerflowMsg.pb-c.h"
#include "ActionState.pb-c.h"
#include "person.pb-c.h"
#include "syn.pb-c.h"
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
        printf("send getPerflowAck");
	ProtoObject * actionGetPerflowAck_object;
	actionGetPerflowAck_object = proto_compose_action_getPerflowack_message(count);
	int result;
	result = send_proto_object(connac_action_state,actionGetPerflowAck_object);
	return result;

}

int action_send_putPerflowAck(int hash){
	ProtoObject * actionPutPerflowack_object;
	actionPutPerflowack_object = proto_compose_action_putPerflowack_message(hash);
	int result;
	result = send_proto_object(connac_action_state, actionPutPerflowack_object);
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
    char* key = actionGetPerflow_recv->key;
    pthread_mutex_lock(&connac_action_lock_get);
    if(strcmp(key,"all")==0){
	INFO_PRINT("action receive getPerflow msg and try to get all states");
	count = connac_locals->action_get_perflow();
	} 
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
    printf("state count");
    connac_locals->action_put_perflow(state);
    action_send_putPerflowAck(state->data);
}


int action_send_perflow(ProtoObject * proto_object){
	int result;
	result = send_proto_object(connac_action_state, proto_object);
	return result;
}

static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    while (1)
    {
        INFO_PRINT("while.........\n");        
	// Attempt to read a JSON string
        char* buffer; 
        buffer = conn_read(connac_action_state);
        if (NULL == buffer)
        {
            ERROR_PRINT("Failed to read from state socket");
            break; 
        }

        INFO_PRINT("while...connread...finish...\n");

	int length = (int)buffer[0];
        int message_type = (int)buffer[1];
        uint8_t * intbuf = (uint8_t*)(buffer+2);

        
	//try put len on first position
        //force translation from char to uint_8
 	
	if(message_type == PROTO_PERSON){
		Person* person_recv = NULL;
        	person_recv = person__unpack(NULL,length,intbuf);

       	 	printf("person name : %s\n", person_recv->name);  

	}
        else if(message_type == PROTO_INFORMATION){
		Information* info_recv = NULL;
        	info_recv = information__unpack(NULL,length,intbuf);

       	 	printf("recieve content name : %s\n", info_recv->content);  

		  
	}else if(message_type == PROTO_ACTION_GETPERFLOWMSG){
		printf("receive a get perflow msg action action action");
		ActionGetPerflowMsg* actionGetPerflow_recv = NULL;
		actionGetPerflow_recv = action_get_perflow_msg__unpack(NULL,length,intbuf);
		handle_get_perflow(actionGetPerflow_recv);

	}else if(message_type == PROTO_ACTION_PUTPERFLOWMSG){
		ActionPutPerflowMsg* actionPutPerflow_recv = NULL;
	        actionPutPerflow_recv = action_put_perflow_msg__unpack(NULL,length,intbuf);
		handle_put_perflow(actionPutPerflow_recv);

	}
	else{ 
            ERROR_PRINT("Unknown type!!!!!");
        }
	
	free(buffer);

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
    printf("state init\n");
    ProtoObject *syn_object	= NULL;
    syn_object = proto_compose_syn_message();
    int send_success = send_proto_object( connac_action_state, syn_object);
	
    if(send_success < 0){
	INFO_PRINT("send message failed");
	return -1;
	}

    free(syn_object);

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
