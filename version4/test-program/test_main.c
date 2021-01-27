#include "local.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <CONNAC.h>


int main()
{

    CONNACLocals locals;
    bzero(&locals,sizeof(locals));
    locals.conn_get_perflow = &local_conn_get_perflow;
    

    printNumber();
}

