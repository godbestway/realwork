#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

#include <pthread.h>
#include <CONNAC.h>

#include "packets.h"

#include "rules.h"
#include "state.h"
#include "handle_packets.h"

#define TCP_PROTO_ID 6
#define ICMP_PROTO_ID 1
#define UDP_PROTO_ID 17
#define MAX_LINE_LEN 256
//+++
static int drop_number=0;
pthread_mutex_t ConnEntryLock;
pthread_mutex_t ActionEntryLock;
//+++

//+++sfc support+++
int new_packet = 0;
 int wait = 0;
cacheState* cache_state;
//+++sfc support+++
struct timeval start_serialize, end_serialize, middle_serialize;
struct interface *to_i;

//Processes a packet read from an interface
void process_packet_inject(struct interface* iface,const struct pcap_pkthdr *hdr, const u_char *data) {
    
    u_int offset = 0;
    
//+++
    gettimeofday(&start_serialize, NULL);    


    if(drop == 1){
	printf("drop == 1");
	drop_number++;
	printf("drop_number %d",drop_number);
	return;
    } 
    
    struct timeval recv_time;
    gettimeofday(&recv_time, NULL);

     
//+++
    
    // Get the ethernet header which is the start of the array.
    struct eth_header *h_ether = malloc(sizeof(struct eth_header));
    memcpy(h_ether,(struct eth_header *) data, sizeof(struct eth_header));
    
    if(h_ether-> type != 8){
        //If this is not an ARP packet or IPV4 return.
        //Free memory
        free(h_ether);
        return;
    }

    // IP header is next after the size of h_ether)
    offset += sizeof(struct eth_header);
    struct ip_header *h_ip = malloc(sizeof(struct ip_header)); 
    memcpy(h_ip, (struct ip_header *) (data + offset), sizeof(struct ip_header));
    offset += (h_ip->ver_ihl & 0x0f) * 4;

    //printf("\n\nProtocol Type: %d\n\n", h_ip->proto);


    
    //handle ICMP packets
    if(h_ip->proto ==ICMP_PROTO_ID){
        struct icmp_header* h_icmp = malloc(sizeof(struct icmp_header));
        memcpy(h_icmp, (struct icmp_header *) (data + offset), sizeof(struct icmp_header));
       
        handle_icmp(h_ether, h_ip, h_icmp, iface, hdr, data);
        return;
        //handle TCP packets
    }else if(h_ip->proto == TCP_PROTO_ID){
        struct tcp_header* h_tcp = malloc(sizeof(struct tcp_header));
        memcpy(h_tcp, (struct tcp_header *)(data + offset), sizeof(struct tcp_header));
        //printf("\nsrc_port %d\n", ntohs(h_tcp->src_port)); 
        //printf("\ndst_port %d\n", ntohs(h_tcp->dst_port));

        handle_tcp(h_ether, h_ip, h_tcp, iface, hdr, data);
 

	//+++
	if (htons(80) == h_tcp->src_port || htons(80) == h_tcp->dst_port)
        { connac_notify_packet_received("HTTP", &recv_time); }
        else if (htons(443) == h_tcp->src_port || htons(443) == h_tcp->dst_port)
        { connac_notify_packet_received("HTTPS", &recv_time); }
        else
         { connac_notify_packet_received("UNKNOWN", &recv_time); }
	//+++

	//while(new_packet == 1){
	//usleep(1);
	//}

	gettimeofday(&end_serialize, NULL);
        long sec = end_serialize.tv_sec - start_serialize.tv_sec;
        long usec = end_serialize.tv_usec - start_serialize.tv_usec;
        long total = (sec * 1000 * 1000) + usec;
			
        //printf("STATS: PERFLOW: TIME TO process packet = %ldus\n", total);
   
        return;
    //handle UPD packets
    }else if(h_ip-> proto == UDP_PROTO_ID){
        struct udp_header* h_udp =  malloc(sizeof(struct udp_header));
        memcpy(h_udp,(struct udp_header *)(data+offset), sizeof(struct udp_header));
        //printf("\nsrc_port %d\n", ntohs(h_udp->src_port)); 
        //printf("\ndst_port %d\n", ntohs(h_udp->dst_port));
        handle_udp(h_ether, h_ip, h_udp, iface, hdr, data); 
        return;
    }else{
        //If not one of the above mentioned packets, we do nothing.
        return;
    }
}


void game_over()
{
	showAllState();
 	exit(0);
}


int main(int argc, char **argv) {
    //intiialize globals

    signal(SIGTERM, game_over);
    signal(SIGINT, game_over);
    signal(SIGQUIT, game_over);

    char err[PCAP_ERRBUF_SIZE];
    pcap_t *pch;

    //Make sure the arguments are correcet.
    if (argc < 2) {
        printf("To hookup to interfaces:  ./firewall interface_1  interface_2 [interface_3, ...] \n");
        printf("To play a pcap file: ./firewall file.pcap\n");
      
        return 0;
    }
    
    //Read in the rules and populate the 
    //rules list
    rule_list = malloc(sizeof(struct rule));

    parse_rules(&rule_list);

    //printf("main print rules\n");
    print_rules(rule_list);
    
    //initialize the error buffer
    char pcap_errbuff[PCAP_ERRBUF_SIZE];
    pcap_errbuff[0]='\0';

    //initialize structures for packet data.
    const u_char* pkt_data=NULL;
    struct pcap_pkthdr hdr;

    
    struct interfaces_map* im = NULL;

        
            struct interface *i =(struct interface*)malloc(sizeof(struct interface));
	    
            i->pcap= pcap_open_live(argv[1],65535,1,0, pcap_errbuff);
            printf("Opening interface %s..\n", argv[1]);


	    if(!(i->pcap)){
		printf("could not open device\n");
		
		}


	    to_i =(struct interface*)malloc(sizeof(struct interface));
	    
            to_i->pcap= pcap_open_live(argv[2],65535,1,0, pcap_errbuff);
            printf("Opening interface %s..\n", argv[2]);


	    if(!(to_i->pcap)){
		printf("could not open device\n");
		
		}
            
            //get the subnet of the interface
            bpf_u_int32 netp, mask;
            pcap_lookupnet(argv[1], &netp, &mask,err);
            i->subnet=(u_int)mask;
            u_char r[4];
            memcpy(&r,&mask,4); 
            
            //get the IP of the interface
            struct ifreq buffer;
            int s = socket(AF_INET, SOCK_DGRAM, 0);
            strcpy(buffer.ifr_name, argv[1]);
            memcpy(&i->name, &argv[1], sizeof(argv[1]));

            if(ioctl(s, SIOCGIFADDR, &buffer)<0){
                printf("Could not populate buffer.");
                exit(1);
            }
            struct sockaddr_in* src_ip_addr = (struct sockaddr_in *)&buffer.ifr_addr;
            memcpy(&i->ip_addr, &src_ip_addr->sin_addr.s_addr, sizeof(i->ip_addr));
         
            //Add the interface to the interface Hash table
            im = (struct interfaces_map*)malloc(sizeof(struct interfaces_map));
            
            memcpy(&im->ip_addr, &i->ip_addr, sizeof(im->ip_addr));
            //printf("%d\n", im->ip_addr);
            im->iface=i;
            //printf("%d\n", i->ip_addr);

	

	CONNACLocals locals;
    	bzero(&locals,sizeof(locals));
    	locals.conn_get_perflow = &local_conn_get_perflow;
    	locals.conn_put_perflow = &local_conn_put_perflow;
    	locals.action_put_perflow = &local_action_put_perflow;
	
	locals.unlock_packet = &local_unlock_packet;

    	connac_init(&locals);

    	// Conn Table Lock
   	 pthread_mutex_init(&ConnEntryLock, NULL);

    	// Action Table Lock
    	pthread_mutex_init(&ActionEntryLock, NULL);

	cache_state= (cacheState*)malloc(sizeof(cacheState));         
       
        //indefinately read from the interfaces 
        while(1){
                pcap_t* t = i->pcap;
                //printf("Reading from interface: %s\n",i->name);
                pkt_data = pcap_next(t , &hdr);
                if(pkt_data){
                    process_packet_inject(i, &hdr, pkt_data);
                }
        }
        return 0;
}

