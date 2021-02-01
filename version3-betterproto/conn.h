#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONNACConn_H_
#define _CONNACConn_H_

#include <pthread.h>
#include <stdint.h>



typedef struct {
	uint8_t * object;
        int length;
}ProtoObject;



///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int conn_active_open(const char *host, unsigned short port);
int conn_passive_open(unsigned short port);
int conn_close(int conn);

ProtoObject conn_read(int conn);
ProtoObject action_read(int conn);
int conn_write(int conn, uint8_t *buf, int len);
int action_write(int conn, uint8_t *buf, int len);


#endif

#ifdef __cplusplus
}
#endif

