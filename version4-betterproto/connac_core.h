#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNACCore_H_
#define _CONNACCore_H_

#include "CONNAC.h"
#include "config.h"

typedef struct {
    
    int pkts_received;
    int flows_active;
    
} CONNACStatistics; 


///// GLOBALS ////////////////////////////////////////////////////////////////
extern ConnacConfig connac_config;
extern CONNACLocals *connac_locals;
extern pthread_mutex_t connac_conn_lock_get;
extern pthread_mutex_t connac_action_lock_get;

#endif

#ifdef __cplusplus
}
#endif
