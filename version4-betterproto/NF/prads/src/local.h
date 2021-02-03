#ifndef _Local_H_
#define _Local_H_

#include <CONNAC.h>

///// DEBUGGING MACROS ///////////////////////////////////////////////////////

typedef struct
{
    int cxid;
    int hash;

}Match;


///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int local_conn_get_one_perflow(connState* conn_state);
int local_conn_get_perflow();
static void *conn_sender(void *arg);

static void *action_sender(void *arg);
int local_action_get_one_perflow(int hash, int cxid);

int local_conn_put_perflow(ConnState* recv_state);
int local_action_get_perflow();
int local_action_put_perflow(ActionState* recv_state);

void showPutConnState();
void showPutActionState();

void showAllCxid();
void showAllState();

void showConnState(connState* conn_state);
void showActionState(actionState* action_state);

#endif
