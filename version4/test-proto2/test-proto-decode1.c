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
    Information info = INFORMATION__INIT;
    unsigned int len;
    uint8_t buf[12];
//    uint8_t header[]={0x3c,0x3c};
//    uint8_t msgtype[]={0x01};

//    info.header.data=header;
//    info.header.len=2;

//    info.msgtype.data=msgtype;
//    info.msgtype.len=1;
    info.personnum=5252;
//    info.price=123.66f;
    info.content = (char*)malloc(CONTENT_LEN);
    info.content="hello";
  
    len = information__get_packed_size(&info);
    printf("size of Student info : %u\n", len);
    uint8_t * buf_2 = NULL;
    uint8_t * buf_3 = NULL;
    buf_2 = (uint8_t*)malloc(len);
    buf_3 = (uint8_t*)calloc(12, sizeof(uint8_t));
    //char* buf [len];
    printf("buf1111111 : %zu\n", sizeof(buf)); 
    printf("buf2222222 : %zu\n", sizeof(buf_2)); 
    printf("buf3333333 : %zu\n", sizeof(buf_3)); 

    information__pack(&info, buf);
    
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


//    printf("buf222222 : %u\n", sizeof(buf)); 
/*    int m;
    for(int m = 0; m < len;m++){
	
	}
  */  
    Information* info_recv = NULL;
    //info_recv = information__unpack(NULL,sizeof(recvBuff),recvBuff);
//    info_recv = information__unpack(NULL,len,buf);
//    printf("info_recv name : %s\n", info_recv->content);

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
/*   
    int recv_len = recv(sockfd, recvBuff, 1024,0);
    printf("recvlen %d\n",recv_len);  
    if(recv_len>0){
	printf("recieve msg\n");
	}
    int real_len=recv_len-4;
    char* dest;
    dest = recvBuff+4; 
    //printf("dest: %zu\n", sizeof(dest));
    int j ;
    for(j=0; j < real_len;j++){
	printf("%x\n",dest[j]);
	}
    printf("!!!!!!!!!!!!!!!!!!!!\n");
    for(j=0; j < recv_len;j++){
	printf("%d: %x\n",j,recvBuff[j]);
	}
	//info_recv = information__unpack(NULL,sizeof(recvBuff),recvBuff);
//     printf("recvBuff : %zu\n", sizeof(recvBuff)); 
      info_recv = information__unpack(NULL,real_len,dest);
    //  info_recv = information__unpack(NULL,13,recvBuff);
      printf("info_recv name : %s\n", info_recv->content);

//    len = information__get_packed_size(recvBuff);
*/
    printf("Hello message sent\n"); 
    printf("buf : %zu\n", sizeof(buf)); 
    //ien = information__get_packed_size(&info);
    if(send(sockfd ,new_buf , len+4 , 0 )>0){
	printf("!!!!!!!!!!!!!!");
	} 
    printf("Hello message sent\n");  
    


    return 0;
}
