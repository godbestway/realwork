#include "SDMBN.h"
#include "SDMBNCore.h"
#include "SDMBNConn.h"
#include "SDMBNDebug.h"
#include "SDMBNJson.h"
#include "SDMBNConfig.h"
#include "event.h"
#include "state.h"
#include <json/json.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

// Thread for handling state messages
static pthread_t state_thread;

// Connection for state messages
int connac_conn_state = -1;


static void send_get_perflow_ack(int id, int count)
{
   /* json_object *ack = json_compose_get_perflow_ack(id, count);
    json_send(ack, sdmbn_conn_state);
    json_object_put(ack); */
}



static int handle_get_perflow(json_object *msg, int id)
{
    // Check if command is supported 
    

    // Parse key
    
    // Get raiseEvents flag
	
    // Wait for get lock to release
    

    // Update statistics
    
    // Set up extensions
   

    // Send ACK
   

    // Release get lock


    return 1;
}

int sdmbn_send_perflow(int id, PerflowKey *key, char *state, int hashkey, 
        int seq)
{
    if (NULL == key || NULL == state || seq < 0)
    { return -1; }

    // Send perflow support state
    json_object *msg = \(id, key, state, hashkey, 
            seq);
    int result = json_send(msg, sdmbn_conn_state);

    // Free JSON object
    json_object_put(msg);

    return result;
}





static void *state_handler(void *arg)
{
    INFO_PRINT("State handling thread started");

    json_tokener_new();

    while (1)
    {
        // Attempt to read a JSON string
        char* buffer =  conn_read(connac_conn_state);
        if (NULL == buffer)
        {
            ERROR_PRINT("Failed to read from state socket");
            break; 
        }

        // Attempt to parse the JSON string
        struct json_object *msg;
        msg = json_tokener_parse(buffer);
        free(buffer);
        if (NULL == msg)
        {
            ERROR_PRINT("Failed to parse JSON from controller: %s", buffer);
            continue;
        }
        DEBUG_PRINT("Parsed msg");

        // Get message id
        json_object *id_field = json_object_object_get(msg, FIELD_ID);
        if (NULL == id_field)
        {
            ERROR_PRINT("JSON from controller has no id: %s", buffer);
            send_error(-1, -1, ERROR_MALFORMED);
            // Free JSON object
            json_object_put(msg);
            continue;
        }
        int id = json_object_get_int(id_field);

        // Get message type
        json_object *type_field = json_object_object_get(msg, FIELD_TYPE);
        if (NULL == type_field)
        {
            ERROR_PRINT("JSON from controller has no type: %s", buffer);
            send_error(id, -1, ERROR_MALFORMED);
            // Free JSON object
            json_object_put(msg);
            continue;
        }
        char *type = (char *)json_object_get_string(type_field);
                
        DEBUG_PRINT("Message: id=%d, type=%s", id, type);

        // Take appropriate action
        // TODO: Check whether we support the action
        if (0 == strcmp(type, COMMAND_GET_PERFLOW))
        { handle_get_perflow(msg, id); }
        else if (0 == strcmp(type, COMMAND_PUT_PERFLOW))
        { handle_put_perflow(msg, id); }
        else
        { 
            ERROR_PRINT("Unknown type: %s", type);
            send_error(id, -1, ERROR_MALFORMED);
        }

        // Free JSON object
        json_object_put(msg);
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
