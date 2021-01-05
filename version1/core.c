#include "SDMBN.h"
#include "Core.h"
#include "Conn.h"
#include "Config.h"
#include "event.h"
#include "state.h"
#include "discovery.h"

#include <json/json.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

SDMBNConfig sdmbn_config;

SDMBNLocals *sdmbn_locals = NULL;

// Global statistics variables
SDMBNStatistics sdmbn_stats;

// Hack for benchmarking
pthread_mutex_t sdmbn_lock_get;

// Thread for sending discovery packets
static pthread_t discovery_thread;

int sdmbn_init(SDMBNLocals *locals)
{
    // Check arguments
    if (NULL == locals)
    { return -1; }

    // Initialize statistics
    bzero(&sdmbn_stats, sizeof(sdmbn_stats));

    // Parse configuration
    sdmbn_parse_config();

    // Store list of MB-specific functions
    sdmbn_locals = locals;

    // Initialize connection lock
    assert(0 == pthread_mutex_init(&sdmbn_lock_conn, NULL));

    // Initialize state
    if (state_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize state"); 
        return -1;
    }

    // Initialize events
    if (events_init() < 0)
    { 
        ERROR_PRINT("Failed to initialize events"); 
        return -1;
    }

    // Create get lock
    assert(0 == pthread_mutex_init(&sdmbn_lock_get, NULL));
    if (sdmbn_config.release_get_pkts > 0 
            || sdmbn_config.release_get_flows > 0) 
    { pthread_mutex_lock(&sdmbn_lock_get); }

    // Create discovery packet sending thread
    if (sdmbn_locals->device != NULL)
    { pthread_create(&discovery_thread, NULL, discovery_send, NULL); }
    else
    { ERROR_PRINT("No device provided"); }

    INFO_PRINT("Initialized");

    return 1;
}

int sdmbn_cleanup()
{
    // Destroy get lock
    pthread_mutex_destroy(&sdmbn_lock_get);

    // Clean-up state
    if (state_cleanup() < 0)
    { ERROR_PRINT("Failed to cleanup state"); }

    // Clean-up events
    if (events_cleanup() < 0)
    { ERROR_PRINT("Failed to cleanup events"); }

    // Call local cleanup function
    if (sdmbn_locals->cleanup != NULL)
    { sdmbn_locals->cleanup(); }

    // Remove list of MB-specific functions
    sdmbn_locals = NULL;
    
    INFO_PRINT("Cleaned-up");

    return 1;
}





