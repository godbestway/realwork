#ifdef __cplusplus
extern "C" {
#endif

#ifndef _action_H_
#define _action_H_

#include <pthread.h>

///// GLOBALS ///////////////////////////////////////////////////////////////
extern int connac_action_state;

///// FUNCTION PROTOTYPES ///////////////////////////////////////////////////
int action_init();
int action_cleanup();
int action_send_getPerflowAck(int count);
#endif

#ifdef __cplusplus
}
#endif
