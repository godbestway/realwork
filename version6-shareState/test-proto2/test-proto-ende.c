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
#include "information.pb-c.h"

#define CONTENT_LEN 32

int main(int argc, char *argv[])
{
 
    //initialize a new Information object
    Information info = INFORMATION__INIT;
    info.personnum=5252;
    info.content = (char*)malloc(CONTENT_LEN);
    info.content="hello";

    //check info length  
    unsigned int len;
    len = information__get_packed_size(&info);
    printf("size of Student info : %u\n", len);
 
    //use length to malloc a space, check pb-c.h to know the buf pointer type
    //here is uint8_t  buf   
    uint8_t * buf = NULL;
    buf = (uint8_t*)malloc(len);
    information__pack(&info, buf);
    

    //create a new buf, add prefix before info
    uint8_t * new_buf = NULL;
    new_buf = (uint8_t*)malloc(len+4);
    new_buf[0] = 12;
    new_buf[1] = 0;
    new_buf[2] = 0;
    new_buf[3] = 0;

    int m;
    for(m = 4; m < len+4; m++){
	new_buf[m] = buf[m-4];
	}


    Information* info_recv = NULL;

    //create socket 
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(18080); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }
   
    //use recvBuff to receive something, get the length of data 
    int recv_len = recv(sockfd, recvBuff, 1024,0);
    printf("recvlen %d\n",recv_len);  
    if(recv_len>0){
	printf("recieve msg\n");
    }

    //ignore the first 4 bytes which are prefix 
    int real_len=recv_len-4;
    char* dest;
    dest = recvBuff+4; 

    //check the received bytes and unpacked bytes(dest) for debug
 /*   int j ;
    for(j=0; j < real_len;j++){
	printf("%x\n",dest[j]);
	}

    for(j=0; j < recv_len;j++){
	printf("%d: %x\n",j,recvBuff[j]);
	}
    printf("recvBuff : %zu\n", sizeof(recvBuff)); 
*/ 
    info_recv = information__unpack(NULL,real_len,dest);
    printf("info_recv name : %s\n", info_recv->content);

    //send the new buf
    printf("Hello message sent\n"); 
    if(send(sockfd ,new_buf , len+4 , 0 )>0){
	printf("!!!!!!!!!!!!!!");
    } 
    printf("Hello message sent\n");  
    
    free(new_buf);

    return 0;
}
