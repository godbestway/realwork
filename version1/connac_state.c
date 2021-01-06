#include "connac_state.h"
#include "debug.h"
#include "protoObject.h"
#include "information.pb-c.h"
#include "person.pb-c.h"

#include "main.h"
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

static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    while (1)
    {
        INFO_PRINT("while.........\n");        
	// Attempt to read a JSON string
        char* buffer; 
        buffer = conn_read(connac_conn_state);
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
 	
	if(message_type == Proto_Person){
		Person* person_recv = NULL;
        	person_recv = person__unpack(NULL,length,intbuf);

       	 	printf("person name : %s\n", person_recv->name);  

	}
        else if(message_type == Proto_Information){
		Information* info_recv = NULL;
        	info_recv = information__unpack(NULL,length,intbuf);

       	 	printf("recieve content name : %s\n", info_recv->content);  

		  
	}
	else{ 
            ERROR_PRINT("Unknown type!!!!!");
        }
	
	free(buffer);

	
	ProtoObject *info_object = NULL;
	//person_object = proto_compose_person_message("xiaoming", 12, "str");
	info_object = proto_compose_information_message(50,"hello a");
	int send_success = send_proto_object( connac_conn_state, info_object);
	if(send_success < 0){
		INFO_PRINT("send message failed");
		return -1;
	}

	free(info_object);
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
            connac_config.ctrl_port_state);
    if (connac_conn_state < 0)
    { 
        ERROR_PRINT("Failed to open state communication channel");
        return connac_conn_state; 
    }
    printf("state init");
  /*  // Create SYN
    json_object *syn = json_compose_syn();

    // Send SYN
    json_send(syn, connac_conn_state);

    // Free JSON object
    json_object_put(syn);
*/
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
