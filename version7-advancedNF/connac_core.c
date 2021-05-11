#include "CONNAC.h"
#include "conn.h"
#include "config.h"
#include "debug.h"
#include "protoObject.h"
#include "connac_state.h"
#include "connac_ac.h"
#include "connac_core.h"
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>

ConnacConfig connac_config;
int ad_nat_firewall;

CONNACLocals *connac_locals = NULL;

CONNACStatistics connac_stats;

// Hack for benchmarking
pthread_mutex_t connac_conn_lock_get;

// Hack for benchmarking
pthread_mutex_t connac_action_lock_get;

int connac_init(CONNACLocals *locals)
{
    // Parse configuration
    connac_parse_config();

    connac_locals = locals;

//+++
    bzero(&connac_stats, sizeof(connac_stats));
//+++
    assert(0 == pthread_mutex_init(&connac_lock_conn, NULL));
    assert(0 == pthread_mutex_init(&connac_lock_action, NULL));

    printf("connac_config.ctrl_share %d\n",connac_config.ctrl_share);

    if(connac_config.ctrl_adnatfire == 1){
	ad_nat_firewall = 1;
	printf("ad_nat_firewall %d\n",ad_nat_firewall);
     }
    
    if(connac_config.ctrl_share == 0){
    // Initialize state
    	if (state_init() < 0)
    	{ 
        	ERROR_PRINT("Failed to initialize state"); 
        	return -1;
    	}
    }

   
    // Initialize state
    if (action_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize action"); 
        return -1;
    }
    
    
    INFO_PRINT("Initialized");
    
    assert(0 == pthread_mutex_init(&connac_conn_lock_get, NULL));

    assert(0 == pthread_mutex_init(&connac_action_lock_get, NULL));
    
   
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


void connac_notify_packet_received(char *type, struct timeval *recv_time)
{
    connac_stats.pkts_received++;
    
    // Output count statistics 
    if (0 == (connac_stats.pkts_received % 10))
    { printf("pkts_received=%d, flows_active=%d\n",
            connac_stats.pkts_received, connac_stats.flows_active); }
}



void connac_notify_flow_created()
{
    connac_stats.flows_active++;
    //printf("connac_stats.flows_active=%d\n",connac_stats.flows_active);
}

void connac_notify_flow_destroyed()
{
    connac_stats.flows_active--;
}



