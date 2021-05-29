#ifndef _Local_H_
#define _Local_H_

#include <CONNAC.h>

///// DEBUGGING MACROS ///////////////////////////////////////////////////////

typedef struct
{
    int cxid;
    int hash;
}Match;

typedef struct
{
    uint8_t* buf;
    int length;

}ProtoObject;




///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int local_conn_get_one_perflow(connState* conn_state);
int local_conn_get_perflow();
int local_conn_put_perflow(ConnState* recv_state);

int local_action_get_one_perflow(Match *match);
int local_action_get_perflow();
int local_action_put_perflow(ActionState* recv_state);

int local_action_get_multiflow();
int local_action_put_multiflow(ActionMultiState* recv_state);
int local_action_get_allflows();
int local_action_put_allflows(ActionAllState* recv_state);

int local_unlock_packet();

ProtoObject* serialize_action_state(actionState* action_state);


void showPutConnState();
void showPutActionState();

void showAllCxid();
void showAllState();

void showConnState(connState* conn_state);
void showActionState(actionState* action_state);


void showAllAssets();



#endif
