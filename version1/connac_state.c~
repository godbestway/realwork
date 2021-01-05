#include "connac_state.h"
#include "information.pb-c.h"
#include "debug.h"
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

        Information* info_recv = NULL;
        
	//try put len on first position
        //force translation from char to uint_8
 
        if(message_type == 1){
		uint8_t * intbuf = (uint8_t*)(buffer+2);
        	info_recv = information__unpack(NULL,length,intbuf);

       	 	printf("recieve content name : %s\n", info_recv->content);  

		  
	}
	
	free(buffer);

	// Take appropriate action
        // TODO: Check whether we support the action
        /*if (0 == strcmp(type, COMMAND_GET_PERFLOW))
        { handle_get_perflow(msg, id); }
        else if (0 == strcmp(type, COMMAND_PUT_PERFLOW))
        { handle_put_perflow(msg, id); }
        else
        { 
            ERROR_PRINT("Unknown type: %s", type);
            send_error(id, -1, ERROR_MALFORMED);
        }*/   

        // Get message id
#define CONTENT_LEN 32
       //initialize a new Information object
    	Information info = INFORMATION__INIT;
    	info.personnum=5252;
    	info.content = (char*)malloc(CONTENT_LEN);
    	info.content="nihao a";

    	//check info length  
    	unsigned int len;
    	len = information__get_packed_size(&info);
    	printf("send size of Student info : %u\n", len);
 
    	//use length to malloc a space, check pb-c.h to know the buf pointer type
    	//here is uint8_t  buf   
    	uint8_t * buf = NULL;
    	buf = (uint8_t*)malloc(len);
    	information__pack(&info, buf);
    #define HEAD_LENGTH 4

    	//create a new buf, add prefix before info
    	uint8_t *new_buf = NULL;
	new_buf = (uint8_t*)malloc(len+HEAD_LENGTH);
    	new_buf[0] = len & 0xff;
    	new_buf[1] = (len>>8)&0xff;
    	new_buf[2] = 0;
    	new_buf[3] = 0x01;

   	 int m;
    	for(m = HEAD_LENGTH; m < len+HEAD_LENGTH; m++){
	new_buf[m] = buf[m-HEAD_LENGTH];
	}

	conn_write(connac_conn_state, new_buf, len+HEAD_LENGTH);

 	free(new_buf);

        // Get message type
        
                
        DEBUG_PRINT("Message: id=%d, type=%s", id, type);

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
