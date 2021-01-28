#include "CONNAC.h"
#include "connac_state.h"
#include "debug.h"
#include "protoObject.h"
#include "information.pb-c.h"
/*
#include "connPutPerflowAckMsg.pb-c.h"
#include "connGetPerflowAckMsg.pb-c.h"
#include "connPutPerflowMsg.pb-c.h"
#include "connGetPerflowMsg.pb-c.h"
#include "ConnState.pb-c.h"
#include "person.pb-c.h"
#include "syn.pb-c.h"
*/
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

/*
int conn_send_getPerflowAck(int count){
        printf("send getPerflowAck");
	ProtoObject * connGetPerflowAck_object;
	connGetPerflowAck_object = proto_compose_conn_getPerflowack_message(count);
	int result;
	result = send_proto_object(connac_conn_state, connGetPerflowAck_object);
	return result;

}

int conn_send_putPerflowAck(int hash){
	ProtoObject * connPerflowAck_object;
	connPerflowAck_object = proto_compose_conn_putPerflowack_message(hash);
	int result;
	result = send_proto_object(connac_conn_state, connPerflowAck_object);
	return result;
}

static int handle_get_perflow(ConnGetPerflowMsg* connGetPerflow_recv)
{
    if (NULL == connac_locals->conn_get_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }
    int count;
    char* key = connGetPerflow_recv->key;
    pthread_mutex_lock(&connac_conn_lock_get);
    if(strcmp(key,"all")==0){
	INFO_PRINT("receive getPerflow msg and try to get all states");
	
	count = connac_locals->conn_get_perflow();
	} 
   printf("perflow count %d",count);
   conn_send_getPerflowAck(count);
   pthread_mutex_unlock(&connac_conn_lock_get);
}

static int handle_put_perflow(ConnPutPerflowMsg* connPutPerflow_recv)
{
    if (NULL == connac_locals->conn_put_perflow)
    {
	printf("this function is not supported");
        return -1; 
    }

    ConnState* state = connPutPerflow_recv->state;
    printf("state received");
    connac_locals->conn_put_perflow(state);
    conn_send_putPerflowAck(state->data);

}
int conn_send_perflow(ProtoObject * proto_object){
	int result;
	result = send_proto_object(connac_conn_state, proto_object);
	return result;
}
*/
static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    while (1)
    {
        INFO_PRINT("while.........\n");        
	// Attempt to read a JSON string
	Information* information; 
        //information = conn_read(connac_conn_state);
        conn_read(connac_conn_state);
        //INFO_PRINT("while...connread...finish...\n");

	/*if(information != NULL){
		printf("personnum %d\n", information->personnum);
		printf("content %s\n", information ->content);


	}else{ 
            ERROR_PRINT("Unknown type!!!!!");
        }*/

        
	//try put len on first position
        //force translation from char to uint_8
 	   
	/*if(message_type == PROTO_PERSON){
		Person* person_recv = NULL;
        	person_recv = person__unpack(NULL,length,intbuf);

       	 	printf("person name : %s\n", person_recv->name);  

	}
        else
	if(message_type == PROTO_INFORMATION){
		Information* info_recv = NULL;
        	info_recv = information__unpack(NULL,length,intbuf);

       	 	printf("recieve content name : %s\n", info_recv->content);  

		  
	}
	else if(message_type == PROTO_CONN_GETPERFLOWMSG){
		ConnGetPerflowMsg* connGetPerflow_recv = NULL;
		connGetPerflow_recv = conn_get_perflow_msg__unpack(NULL,length,intbuf);
		handle_get_perflow(connGetPerflow_recv);

	}else if(message_type == PROTO_CONN_PUTPERFLOWMSG){
		ConnPutPerflowMsg* connPutPerflow_recv = NULL;
	        connPutPerflow_recv = conn_put_perflow_msg__unpack(NULL,length,intbuf);
		handle_put_perflow(connPutPerflow_recv);

	}*/
	
	
	free(information);

	
        // Get message type
        
            

        // Free JSON object
        
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


    /*ProtoObject *syn_object	= NULL;
    syn_object = proto_compose_syn_message();
	
    int send_success = send_proto_object( connac_conn_state, syn_object);
    //int send_success = send_proto_object( connac_conn_state, info_object);
    if(send_success < 0){
	INFO_PRINT("send message failed");
	return -1;
     }

    free(syn_object);*/

	
    int send_success = send_information_message( connac_conn_state, 112, "test");
    //int send_success = send_proto_object( connac_conn_state, info_object);
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
