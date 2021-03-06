#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef struct _prads_stat {
    uint32_t got_packets;   /* number of packets received by prads */
    uint32_t eth_recv;      /* number of Ethernet packets received */
    uint32_t arp_recv;      /* number of ARP packets received */
    uint32_t otherl_recv;   /* number of other Link layer packets received */
    uint32_t vlan_recv;     /* number of VLAN packets received */
    uint32_t ip4_recv;      /* number of IPv4 packets received */
    uint32_t ip6_recv;      /* number of IPv6 packets received */
    uint32_t ip4ip_recv;    /* number of IP4/6 packets in IPv4 packets */
    uint32_t ip6ip_recv;    /* number of IP4/6 packets in IPv6 packets */
    uint32_t gre_recv;      /* number of GRE packets received */
    uint32_t tcp_recv;      /* number of tcp packets received */
    uint32_t udp_recv;      /* number of udp packets received */
    uint32_t icmp_recv;     /* number of icmp packets received */
    uint32_t othert_recv;   /* number of other transport layer packets received */
    uint32_t assets;        /* total number of assets detected */
    uint32_t tcp_os_assets; /* total number of tcp os assets detected */
    uint32_t udp_os_assets; /* total number of udp os assets detected */
    uint32_t icmp_os_assets;/* total number of icmp os assets detected */
    uint32_t dhcp_os_assets;/* total number of dhcp os assets detected */
    uint32_t tcp_services;  /* total number of tcp services detected */
    uint32_t tcp_clients;   /* total number of tcp clients detected */
    uint32_t udp_services;  /* total number of udp services detected */
    uint32_t udp_clients;   /* total number of tcp clients detected */
} prads_stat;
typedef uint8_t byte;

static byte base64_encode_bits(byte data)
{
    if (data < 26)
        return (data + 'A');
    if (data < 52)
        return (data - 26 + 'a');
    if (data < 62)
        return (data - 52 + '0');
    if (data == 62)
        return '+';
    if (data == 63)
        return '/';
    return 0;
}

char *sdmbn_base64_encode(void *blob, int size)
{
    if (NULL == blob || size < 1)
    { return NULL; }
    byte *ptrBlob = (byte *)blob;
    char *result = (char *)malloc(size*2+1);
    if (NULL == result)
    { return NULL; }
    char *ptrResult = result;
    while (size > 0)
    {
        byte lower = *ptrBlob & 0x0F;
        byte upper = (*ptrBlob & 0xF0) >> 4;
        *ptrResult = base64_encode_bits(lower);
        ptrResult++;
        *ptrResult = base64_encode_bits(upper);
        ptrResult++;
        ptrBlob++;
        size += -1;
    }
    *ptrResult = 0;
    return result;
}

static byte base64_decode_bits(byte data)
{
    if (data >= 'A' && data <= 'Z')
        return (data - 'A');
    if (data >= 'a' && data <= 'z')
        return (data + 26 - 'a');
    if (data >= '0' && data <= '9')
        return (data + 52 - '0');
    if (data == '+')
        return 62;
    if (data == '/')
        return 63;
    return 0;
}

void *sdmbn_base64_decode(char *blob)
{
    if (NULL == blob)
    { return NULL; }
    byte *ptrBlob = (byte *)blob;
    int size = strlen(blob);
    void *result = malloc(size/2);
    if (NULL == result)
    { return NULL; }
    char *ptrResult = (char *)result;
    while (size > 0)
    {
        byte lower = base64_decode_bits(*ptrBlob);
        ptrBlob++;
        byte upper = base64_decode_bits(*ptrBlob);
        ptrBlob++;
        *ptrResult = (upper << 4) | lower;
        ptrResult++;
        size += -2;
    }
//    *ptrResult = 0;
    return result;
}

int main(){

	prads_stat pr_s;
	pr_s.got_packets = 10;
	pr_s.eth_recv = 9;

	char *state = sdmbn_base64_encode(&pr_s, sizeof(pr_s));
	int i;
	for(i = 0; i < sizeof(pr_s)*2+1; i++){
		printf("%x\n",state[i]);
	}
	
	//memset((void *)pr_s, 0, sizeof(pr_s));
	pr_s.got_packets = 0;
	pr_s.eth_recv = 0;
	printf("pr_s.got_packets %u\n",pr_s.got_packets);
	printf("pr_s.eth_recv %u\n",pr_s.eth_recv);

	prads_stat *received = sdmbn_base64_decode(state);

	memcpy(&pr_s, received, sizeof(pr_s));
	printf("pr_s.got_packets %u\n",pr_s.got_packets);
	printf("pr_s.eth_recv %u\n",pr_s.eth_recv);
}






