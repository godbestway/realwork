#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

typedef struct _ether_header {
    uint8_t ether_dst[6];        /* destination MAC */

} ether_header;

typedef struct _packetInfo {
    ether_header eth_hdr;        /* destination MAC */

} packetInfo;

typedef struct _connState {
    uint8_t ether_dst[6];        /* destination MAC */
} connState;



line* head;
line* put_head;

void initLine();

int local_get_perflow();

void display(line * head);

int main()
{
    uint8_t src_mac[6] = {11,12,23,23,78,34};
    ether_header *eth_hdr;
    
    eth_hdr = (ether_header *) calloc(1, sizeof(ether_header));
    eth_hdr->ether_dst = src_mac;
    eth_hdr->ether_dst[1] = src_mac[1];
    eth_hdr->ether_dst[2] = src_mac[2];
    eth_hdr->ether_dst[3] = src_mac[3];
    eth_hdr->ether_dst[4] = src_mac[4];
    eth_hdr->ether_dst[5] = src_mac[5];*/
    printf("0: %u\n",eth_hdr->ether_dst[0]);
    printf("1: %u\n",eth_hdr->ether_dst[1]);
    printf("2: %u\n",eth_hdr->ether_dst[2]);
    printf("3: %u\n",eth_hdr->ether_dst[3]);
    printf("4: %u\n",eth_hdr->ether_dst[4]);
    printf("5: %u\n",eth_hdr->ether_dst[5]);
/*    packetInfo *pi;
    pi = (packetInfo) calloc(1,sizeof(packetInfo));
    pi -> eth_hdr = eth_hdr;

    connState *conn_state;
    conn_state = (connState)calloc(1,sizeof(connState));
    conn_state -> ether_dst = pi->eth_hdr->ether_dst;
*/

    char a[2];
    a[0] = 0x0c;
    a[1] = 12;
    int b; 
    //b = a[1] & 0xff;

    b = (int)((a[0] & 0xff) |( (a[1] & 0xff)<<8));
    char *buf = (char*)malloc(2);

    int c = (int)a[1];
    buf[0] = 0x0a;
    buf[1] = 0x02;
    uint8_t* bufint = (uint8_t*)buf; 
    int j = strlen(buf);
    //printf("strlen %d\n ",c);
    printf("size %x\n", bufint[0]); 
    int pid = getpid();
    char hostname[1024];
    memset(hostname, 0, 1024);
    gethostname(hostname, 1024);    
    printf("hostname %s\n", hostname);
    printf("pid %d\n",pid);

     head=(line*)malloc(sizeof(line));    
     put_head=(line*)malloc(sizeof(line));    
     //initLine();
     local_put_perflow();
   

    
 
//    printf("int: %d\n",b);
   
}

void initLine(){
    
   
    head->prior=NULL;
    head->next=NULL;
    head->data=1;
    
    line * list=head;
    int i;
    for (i=2; i<=5; i++) {
       
        line * body=(line*)malloc(sizeof(line));
        body->prior=NULL;
        body->next=NULL;
        body->data=i;

        
        list->prior=body;
        body->next=list;
	/*printf("body->data %d\n", body->data);
	if(body->next != NULL){
	printf("body->next %d\n", body ->next->data);
	}
	if(body->prior != NULL){
        printf("body->prior %d\n",body -> prior->data);
	} */       
        list = body;
	/*printf("list->data %d\n", list->data);
	if(list->next != NULL){
	printf("list->next %d\n", list ->next->data);
	}
	if(list->prior != NULL){
        printf("list->prior %d\n",list -> prior->data);
	} */       
    }
    //printf("list:next %d",list->next->next->next->next->data);
    //input = list;    
    //printf("input:next %d",input->next->next->next->next->data);
    head = list;
}

int local_put_perflow(){

    int i = 1;
    for(i; i < 5 ;i++){



    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    in_state->data = i; 
     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(put_head != NULL){
         put_head->prior = in_state;
	 in_state->next = put_head; 
	}
    else{
	
	in_state->next = NULL;
	}
    put_head = in_state;
    
	}

    display(put_head);   
}



int local_get_perflow(){
    line * temp= head;
    while (temp) { 
       
    printf("while data: %d\n",temp->data);
    temp=temp->next;
    }
	return 1;
}

void display(line * head){
    line * temp=head;
    while (temp) {
        
        if (temp->next==NULL) {
            printf("%d\n",temp->data);
        }else{
            printf("%d <-> ",temp->data);
        }
        temp=temp->next;
    }
}
