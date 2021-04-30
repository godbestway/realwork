#include "handle_packets.h"
extern cacheState* cache_state;
extern struct timeval start_serialize, middle_serialize;

void pass_packet(struct interface* iface, struct ip_header* h_ip, u_char* data, struct pcap_pkthdr* hdr){

	//printf("pass the packet\n");
	printf("");
}

//Appropriately handles TCP packets seen
//By the Firewall
void handle_tcp(struct eth_header* h_ether, struct ip_header* h_ip, struct tcp_header* h_tcp, struct interface* iface, const struct pcap_pkthdr *hdr, u_char* data){

    //state_expunge_expired();
    rule_type_t rt;


    packetinfo pstruct = {0};
    packetinfo *pi = &pstruct;
    memcpy(pi->saddr, h_ip->saddr,4);
    memcpy(pi->daddr,h_ip->daddr,4);	
    pi->src_port = h_tcp->src_port;
    pi->dst_port = h_tcp->dst_port;
    pi->proto = h_ip->proto;

    char* sadr = ip_string(pi->saddr);
    char* dadr = ip_string(pi->daddr);
    u_short src_port = pi->src_port;
    u_short dst_port = pi->dst_port;

    /*if((strcmp(ip_string(cache_state->src_ip), sadr) == 0)&& (strcmp(ip_string(cache_state->dst_ip), dadr) == 0) 
			&& (cache_state->src_prt == src_port) && (cache_state->dst_prt == dst_port)){
	rt = cache_state->state;
	printf("match cache state\n");
    }
    else{*/
    	//get the Rule that applies to this packet
    	process_with_conn_state(pi);
	rt = process_with_action_state(pi);
	//}
/*
	gettimeofday(&middle_serialize, NULL);
        long sec = middle_serialize.tv_sec - start_serialize.tv_sec;
        long usec = middle_serialize.tv_usec - start_serialize.tv_usec;
        long total = (sec * 1000 * 1000) + usec;
			
        printf("STATS: PERFLOW: MIDDLE TIME TO process packet = %ldus\n", total);
*/
	//printf("not match cache state\n");
    //}
   
    //printf("\n\nRule Type: %i\n", rt);
    if(rt == BLOCK){
        //printf("TCP: Blocking the packet.\n");
        //Free the packets
        free(h_ether);
        free(h_tcp);
        return;
    }else if(rt == PASS){
        //printf("TCP: Forwarding the packet.\n");
        pass_packet(iface, h_ip, data, hdr);
        //free the packets
        //free(h_ip);
        free(h_ether);
        free(h_tcp);
        //h_ip is freed in pass_packet when it is done being used.
        return;
    }
}

//Appropriately handles UDP packets seen
//By the Firewall
void handle_udp(struct eth_header* h_ether, struct ip_header* h_ip, struct udp_header* h_udp, struct interface* iface, const struct pcap_pkthdr *hdr, u_char* data){
    
    struct interface* i =NULL;
    char* sadr = ip_string(h_ip->saddr);
    char* dadr = ip_string(h_ip->daddr);
    rule_type_t rt;
   
    //get the Rule that applies to this packet
    rt = get_firewall_action(rule_list, sadr, dadr, ntohs(h_udp->src_port), ntohs(h_udp->dst_port));
    //Free interface memory
    free(i);
   
    free(sadr);
    free(dadr);
    printf("\n\nRule Type: %i\n", rt);
   
    if(rt == BLOCK){
        printf("UDP: Blocking the packet.\n");
        free(h_udp);
        free(h_ether);
        return;
    }else if(rt==PASS){
        printf("UDP: Forwarding the packet.\n"); 
        pass_packet(iface, h_ip, data, hdr);
        //free the packets
        free(h_ether);
        free(h_udp);
        //h_ip is freed in pass_packet when it is done being used.
        return;
    }
}

//Appropriately handles ICMP packets seen
//By the Firewall
void handle_icmp(struct eth_header* h_ether, struct ip_header* h_ip, struct icmp_header* h_icmp, struct interface* iface, const struct pcap_pkthdr *hdr, u_char* data){
 
    struct interface* i =NULL;
    char* sadr = ip_string(h_ip->saddr);
    char* dadr = ip_string(h_ip->daddr);
    rule_type_t rt;
   
    //get the Rule that applies to this packet
    rt = get_firewall_action(rule_list, sadr, dadr, NULL, NULL);
    //Free interface memory
    free(i);
   
    free(sadr);
    free(dadr);
    printf("\n\nRule Type: %i\n", rt);
   
   if(rt == BLOCK){
        printf("ICMP: Blocking the packet.\n");
        free(h_ether);
        free(h_icmp);
        return;
    }else if(rt==PASS){
        printf("ICMP: Forwarding the packet.\n"); 
        pass_packet(iface, h_ip, data, hdr);
        //free the packets
        free(h_icmp);
        free(h_ether);
        //h_ip is freed in pass_packet when it is done being used.
        return;
    }
}
