#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <sys/time.h>
#include "information.pb-c.h"

#define CONTENT_LEN 32
#define HEAD_LENGTH 4


int main(int argc, char *argv[])
{
    uint32_t cxid;
    cxid = 10000;

    uint8_t tos = cxid;
    uint8_t ttl = cxid>>8;
    
    printf("tos: %u\n",tos);
    printf("ttl: %u\n",ttl);

    uint16_t ttl_16;
    cxid = (uint16_t)(ttl <<8) | (uint16_t)tos;
    printf("cxid %u\n",cxid);
	struct timeval start_serialize, end_serialize;
    gettimeofday(&start_serialize, NULL);    

    int i = 0;
    while(i < 1000000){
	if(cxid > 0){
		if(cxid < 100000){
			if(cxid < 50000){
				if(cxid < 20000){
					if(cxid < 10000){
						cxid = 10000;			
					}
				}
			}
		
		}

	}

	i++;


	} 

   
    gettimeofday(&end_serialize, NULL);
    long sec = end_serialize.tv_sec - start_serialize.tv_sec;
    long usec = end_serialize.tv_usec - start_serialize.tv_usec;
    long total = (sec * 1000 * 1000) + usec;
			
    printf("STATS: PERFLOW: TIME TO process packet = %ldus\n", total);

   gettimeofday(&start_serialize, NULL); 
   i = 0;
   while(i < 100000){
	if(cxid < 100000){
		cxid = 10000;
	}
	i++;
   }   

  
    gettimeofday(&end_serialize, NULL);
    sec = end_serialize.tv_sec - start_serialize.tv_sec;
    usec = end_serialize.tv_usec - start_serialize.tv_usec;
    total = (sec * 1000 * 1000) + usec;
			
    printf("STATS: PERFLOW: TIME TO process packet = %ldus\n", total);

    

    return 0;
}
















