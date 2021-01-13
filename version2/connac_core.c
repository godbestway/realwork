#include "CONNAC.h"
#include "conn.h"
#include "config.h"
#include "debug.h"
#include "connac_state.h"
#include "connac_ac.h"
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>

ConnacConfig connac_config;
CONNACLocals *connac_locals = NULL;

int connac_init(CONNACLocals *locals)
{
    // Parse configuration
    connac_parse_config();

    connac_locals = locals;
	
    
    // Initialize state
    if (state_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize state"); 
        return -1;
    }
    // Initialize state
    if (action_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize action"); 
        return -1;
    }
    
    INFO_PRINT("Initialized");
    
   
}


int connac_cleanup()
{
    // Clean-up state
    if (state_cleanup() < 0)
    { ERROR_PRINT("Failed to cleanup state"); }

    // Clean-up events
    if (action_cleanup() < 0)
    { ERROR_PRINT("Failed to cleanup events"); }

        
    INFO_PRINT("Cleaned-up");

    return 1;
}






