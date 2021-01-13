#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNACConn_H_
#define _CONNACConn_H_

#include <pthread.h>
#include <stdint.h>

extern pthread_mutex_t connac_lock_conn;

///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int conn_active_open(const char *host, unsigned short port);
int conn_passive_open(unsigned short port);
int conn_close(int conn);
char *conn_read(int conn);
int conn_write(int conn, uint8_t *buf, int len);


#endif

#ifdef __cplusplus
}
#endif

