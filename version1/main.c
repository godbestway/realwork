#include "conn.h"
#include "config.h"
#include "debug.h"
#include "connac_state.h"
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

ConnacConfig connac_config;


int main()
{
    // Parse configuration
    connac_parse_config();
	
  


    
    // Initialize state
    if (state_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize state"); 
        return -1;
    }
    
    INFO_PRINT("Initialized");

    while(1){

	}
    
    return 1;
}






